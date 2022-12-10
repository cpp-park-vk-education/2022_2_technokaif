#include "tools.h"
#include <string>
#include <fstream>

class OpenVPNClient {
private:
    const std::string _configFileName = "config.ovpn";
    int pid = 0;

public:
    void updateConfig(const std::string& cfg);

    void runOpenVPN();
    void stopOpenVPN();
};

class Client {
private:

    boost::asio::posix::stream_descriptor _inputStream;

    boost::asio::ip::tcp::socket _socket;

    std::string _ip = "127.0.0.1";
    unsigned int _port = 80;

    OpenVPNClient oVPNclient;
    VPNContext _context;

public:
    Client(boost::asio::io_context& context, std::string ip, unsigned int port);
    ~Client() {}

    void sendData();
    void getData();
    void getVPNContext();  // from console
    void connect();
    void stopConnection();
    bool isStateStop() { return _context.state == VPNMode::stopped; }
};