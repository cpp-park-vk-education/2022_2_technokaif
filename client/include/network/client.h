#ifndef _CLIENT_H_
#define _CLIENT_H_

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
    int pid = -1;

 public:
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

#endif  // _CLIENT_H_
