#include "tools.h"
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

struct OptionalUrl {
    std:: string url;
    std::vector<std::string> ipList;
};

class Config {
public:
    Config(const std::string& fileName = "client.cfg");
    void write(const std::string& buffer);
    std::string& read();

private:
    std::ifstream file_ptr;
};

class IHandler {
public:
    virtual ~IHandler() = 0;
    virtual void handle(boost::asio::const_buffer );
    void reply();

private:
    boost::asio::const_buffer msg;
};

class UrlToIpConverter {
public:
    void runConvert();
    std::vector<OptionalUrl> getOptionalUrlList();

private:
    std::vector<OptionalUrl> vpnList;
    VPNContext vpnContext;

    std::vector<std::string> nsRequest(std::string url);
};

class MakeConfigurationFiles {
    MakeConfigurationFiles(VPNMode , std::vector<OptionalUrl> );
    virtual Config MakeServerConfig(VPNMode ) = 0;
    virtual Config MakeClientConfig(VPNMode ) = 0;
};

class OVPNRunner {
public:
    MakeConfigurationFiles* confFilesMaker;
    
    void RunOpenVPNServer();
    void StopOpenVPNServer();

    Config GetClientConfig();

private:
    Config ServerConfig;
    Config ClientConfig;
};

class VpnMsgHandler : public IHandler {
public:
    void handle(boost::asio::const_buffer ) override;
    Config reply();

private:
    void inputAnalyze();

    VPNContext fromVpnMsgToVpnContext(boost::asio::const_buffer vpnMsg);
    void setVpnContext(const VPNContext& ) {}
    void setVpnMode(const VPNMode& ) {}
    void setVpnList(const std::vector<OptionalUrl>& ) {}

    std::vector<OptionalUrl> convertVpnContextToVpnList(const VPNContext& );
    
private:
    VPNMode vpnMode;
    std::vector<OptionalUrl> vpnList;
    UrlToIpConverter* urlConverter;
    OVPNRunner* ovpnRunner;
};