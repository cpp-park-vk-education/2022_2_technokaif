#include "../../include/network/client.h"

#include <algorithm>

using json = nlohmann::json;


// ----------------------------- OpenVPNClient -------------------------------

OpenVPNClient::~OpenVPNClient() {
    if (pid != 0) {
        kill(pid, SIGKILL);
    }
}

void OpenVPNClient::updateConfig(const std::string& cfg) {
    std::fstream out(_configFileName);
    out.clear();
    out << cfg;
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
    if (pid != -1) {
        kill(pid, SIGKILL);
    }
}


// ----------------------------- Client -------------------------------

void Client::sendData() {
    json j;

    j["state"] = _context.state;
    j["mode"] = _context.mode;

    if (_context.mode == VPNMode::OPTIONAL) {
        for (size_t i = 0; i < _context.urlList.size(); ++i) {
            j["urlList"].push_back(_context.urlList[i]);
        }
    }
    std::cout << j.dump() << std::endl;

    _socket.send(boost::asio::buffer(j.dump()));
}

void Client::getData() {
    std::string input;
    input.resize(16384);
    _socket.receive(boost::asio::buffer(input, 16384));

    std::cout << "input: " << input << std::endl;

    json j = json::parse(input);

    std::string config;
    for (auto &str : j["config"]) {
        config += str;
        config += '\n';
    }

    oVPNclient.updateConfig(config);
    oVPNclient.runOpenVPN();
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

    std::cout << "connection close" << std::endl;
}
