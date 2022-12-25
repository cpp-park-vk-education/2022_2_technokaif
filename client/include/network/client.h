#ifndef CLIENT_H
#define CLIENT_H

#include "../tools/utils.h"

class UrlToIpConverter {
public:
    void runConvert(std::vector<std::string> urlList);
    std::vector<std::string> getIpList();

private:
    std::vector<std::string> ipList;
    std::vector<std::string> nsRequest(std::string url);
};

class OpenVPNClient {
 private:
    const std::string _configFileName = "config.ovpn";
    std::string pwd;
    std::string openvpn_path;
    // int pid = -1;

    boost::process::child openvpn;

 public:
    OpenVPNClient();
    ~OpenVPNClient();

    void updateConfig(const std::string& cfg);

    void runOpenVPN();
    void stopOpenVPN();
};

class Client {
 private:
    boost::asio::posix::stream_descriptor _inputStream;
    boost::asio::ip::tcp::socket _socket;

    std::string _ip = "127.0.0.1";
    uint _port = 80;

    OpenVPNClient _oVPNclient;
    VPNContext _context;

 public:
    Client(boost::asio::io_context& context, std::string ip, uint port);
    ~Client() {}

    void setEndpoint(std::string ip, uint port);

    void sendData();
    void getData();
    void setVPNContext(RunStatus state, VPNMode mode, const std::vector<std::string>& urls);
    void connect();
    void stopConnection();
    bool isStateStop() { return _context.state == RunStatus::STOPPED; }
};

#endif  // CLIENT_H