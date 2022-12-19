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
