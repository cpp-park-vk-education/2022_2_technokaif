#include "client.h"

#include "json.hpp"

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
    // pid = execl("/usr/sbin/openvpn", "/usr/sbin/openvpn", _configFileName.c_str(), NULL);
    if (pid != -1) {
        kill(pid, SIGKILL);
    }
    pid = fork();
    if (pid == 0) {
        // pid = execl("./a.out", "a.out", NULL);
        // pid = execl("/usr/sbin/openvpn", "/usr/sbin/openvpn", "config-test.ovpn", ">output", NULL);
        // pid = system("openvpn config-test.ovpn >output");
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

    // json j = json::parse(input);
    // input = j["config"];

    std::ifstream fin("config.ovpn");
    std::ostringstream sout;
    
    std::copy(std::istreambuf_iterator<char>(fin),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(sout));

    oVPNclient.updateConfig(sout.str());
    oVPNclient.runOpenVPN();
}

Client::Client(boost::asio::io_context& context, std::string ip, unsigned int port) :
    _inputStream(context, STDIN_FILENO), _socket(context), _ip(ip), _port(port) {}


void Client::getVPNContext() {
    std::cout << "Choose a state of VPN run:" << std::endl;
    std::cout << "1 - runTotal" << std::endl;
    std::cout << "2 - runOptional" << std::endl;
    std::cout << "3 - stopped" << std::endl;
    unsigned int state = 0;
    bool flag = true;
    _context.urlList.clear();
    while (flag) {
        std::cin >> state;
        switch (state) {
            case 1:
                _context.state = VPNMode::runTotal;
                flag = false;
                break;
            case 2:
                _context.state = VPNMode::runOptional;
                {
                    std::cout << "Write a count of urls: ";
                    size_t count = 0;
                    std::cin >> count;
                    std::string url;
                    for (size_t i = 0; i < count; ++i) {
                        std::cin >> url;
                        _context.urlList.push_back(url);
                    }
                    
                    // std::string url;
                    // while (std::cin >> url) {
                    //     _context.urlList.push_back(url);
                    // }
                    // std::cin.clear();
                }
                flag = false;
                break;
            case 3:
                _context.state = VPNMode::stopped;
                flag = false;
                break;
            default:
                break;
        }
    }
    for (size_t i = 0; i < _context.urlList.size(); ++i) {
        std::cout << _context.urlList[i] << ", ";
    }
    std::cout << std::endl;
}

void Client::connect() {
    // TODO : установить соединение с сервером и отправить серверу VPNContext
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
