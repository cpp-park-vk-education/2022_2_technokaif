#include "client.h"

#include "json.hpp"

using json = nlohmann::json;

// ----------------------------- OpenVPNClient -------------------------------

OpenVPNClient::~OpenVPNClient() {
    if (pid != 0) {
        kill(pid, SIGKILL);
    }
}

void OpenVPNClient::clearConfig() {
    std::fstream out(_configFileName);
    out.clear();
}

void OpenVPNClient::updateConfig(const std::string& cfg) {
    std::fstream out(_configFileName);
    out << cfg;
}

void OpenVPNClient::runOpenVPN() {
    // pid = execl("/usr/sbin/openvpn", "/usr/sbin/openvpn", _configFileName.c_str(), NULL);
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
    if (_context.state == VPNMode::runOptional) {
        for (size_t i = 0; i < _context.urlList.size(); ++i) {
            j["urlList"].push_back(_context.urlList[i]);
        }
    }
    std::cout << j.dump() << std::endl;
    _socket.send(boost::asio::buffer(j.dump()));
}

void Client::getData() {
    std::string input;
    input.resize(512);
    _socket.receive(boost::asio::buffer(input, 512));

    oVPNclient.clearConfig();
    while (!input.empty()) {
        oVPNclient.updateConfig(input);
        oVPNclient.updateConfig("\n");
        _socket.receive(boost::asio::buffer(input, 512));
    }

    oVPNclient.runOpenVPN();
}

Client::Client(boost::asio::io_context& context, std::string ip, unsigned int port) :
    _inputStream(context, STDIN_FILENO), _socket(context), _ip(ip), _port(port) {}


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
}
