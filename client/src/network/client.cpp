#include "../../include/network/client.h"

#include <algorithm>

using json = nlohmann::json;


// ----------------------------- OpenVPNClient -------------------------------

OpenVPNClient::~OpenVPNClient() {
    system("sudo killall openvpn");
}

void OpenVPNClient::updateConfig(const std::string& cfg) {
    std::fstream out;
    out.open(_configFileName, std::ios::out | std::ios::trunc);
    out << cfg;
    out.close();
}

void OpenVPNClient::runOpenVPN() {
    if (pid != -1) {
        kill(pid, SIGKILL);
    }

    pid = fork();
    if (pid == 0) {
        pid = execl("./run-openvpn", "./run-openvpn", NULL);
    }

    std::cout << "pid = " << pid << std::endl;
}

void OpenVPNClient::stopOpenVPN()  {
    // if (pid != 0) {
    //     kill(pid, SIGKILL);
    // }
    system("sudo killall openvpn");
}

// ----------------------------- UrlToIpConverter -------------------------------

std::vector<std::string> UrlToIpConverter::nsRequest(std::string url) {
  // TODO(Ilya): метод, запрашивающий по url ip лист

  std::string host;
  const std::string header = "https://";
  int pos = url.find(header);
  if (pos == 0) {
    host = url.substr(header.size());
  } else {
    host = url;
  }

  std::vector<std::string> ipVector;
  std::string nslookup_exec = "nslookup ";
  nslookup_exec += host;

  boost::process::ipstream is;
  boost::process::child ns_proc(nslookup_exec, boost::process::std_out > is);
  ns_proc.wait();

  std::string line;
  bool skip = true;
  while(std::getline(is, line)) {
    if (line.find("Address:") != std::string::npos) {
        if (skip) {
            skip = false;
            continue;
        }

        std::string ip;
        for (int i = 8; i < int(line.size()); ++i) {
            if (!isspace(line[i])) {
                ip.push_back(line[i]);
            }
        }
        if (ip.find(":") == std::string::npos) {
            ipVector.push_back(ip);
        }
    }
  }

  return ipVector;
}

void UrlToIpConverter::runConvert(std::vector<std::string> urlList) {
  // TODO(Ilya): метод, реализующий конвертацию url ссылок в ip лист

  for (const auto &url : urlList) {
    std::vector<std::string> urlIpList = nsRequest(url);
    for (auto ip : urlIpList) {
        ipList.push_back(ip);
    }
  }
}

std::vector<std::string>
UrlToIpConverter::getIpList() {
  // TODO(Ilya): метод, возвращающий вектор структур из ip листа и url
  // (т.е структуру со всеми необходимыми данными)

  return ipList;
}

// ----------------------------- Client -------------------------------

void Client::sendData() {
    json j;

    j["state"] = _context.state;
    j["mode"] = _context.mode;

    if (_context.mode == VPNMode::OPTIONAL) {
        UrlToIpConverter converter;
        converter.runConvert(_context.urlList);
        std::vector<std::string> ipList = converter.getIpList();
        
        for (int i = 0; i < ipList.size(); ++i) {
            j["ipList"].push_back(ipList[i]);
        }
    }
    std::cout << j.dump() << std::endl;

    _socket.send(boost::asio::buffer(j.dump()));
}

void Client::getData() {
    // input.resize(1 << 13);
    std::cout << "----- INPUT BEFORE RECEIVING -----" << std::endl;
    // _socket.read_some(boost::asio::buffer(input, input.size()));
    // boost::asio::read_until(_socket, boost::asio::buffer(input, input.size()), '}');

    boost::asio::streambuf b;
    boost::asio::read_until(_socket, b, '}');
    std::istream is(&b);
    std::string input;
    std::copy(std::istreambuf_iterator<char>(is),
        std::istreambuf_iterator<char>(),
        std::back_inserter(input));

    std::cout << "----- INPUT AFTER RECEIVING -----" << std::endl;
    std::cout << "INPUT LENGTH = " << input.length() << std::endl;
    std::cout << input << std::endl;
    std::cout << "----- END OF INPUT -----" << std::endl;

    json j = json::parse(input);

    std::string config;
    for (auto &str : j["config"]) {
        config += str;
        config += '\n';
    }

    _oVPNclient.updateConfig(config);
    _oVPNclient.runOpenVPN();
}

Client::Client(boost::asio::io_context& context, std::string ip, unsigned int port) :
    _inputStream(context, STDIN_FILENO), _socket(context), _ip(ip), _port(port) {}

void Client::setVPNContext(RunStatus state, VPNMode mode, const std::vector<std::string>& urls) {
    _context.state = state;
    _context.mode = mode;
    _context.urlList = urls;
}

void Client::connect() {
    if (_socket.is_open()) {
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        _socket.close();
    }
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(_ip), _port);

    _socket.connect(ep);
}

void Client::stopConnection() {
    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

    _inputStream.close(); 
    _socket.close();
    
    _oVPNclient.stopOpenVPN();

    std::cout << "connection close" << std::endl;
}

void Client::setEndpoint(std::string ip, uint port) {
    _ip = ip;
    _port = port;
}
