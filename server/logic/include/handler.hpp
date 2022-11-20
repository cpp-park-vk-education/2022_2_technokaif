#include "tools.h"
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

struct OptionalUrl {
    std::string url;
    std::vector<std::string> ipList;
};

class Config {
public:
    explicit Config(const std::string& fileName = "client.cfg");
    void write(const std::string& buffer);
    std::string& read();

private:
    std::ifstream file_ptr;
};

class IHandler {
public:
    virtual ~IHandler() = 0;
    virtual void handle(boost::asio::const_buffer ) = 0;
    virtual Config reply() = 0;

private:
    boost::asio::const_buffer msg;
};

class UrlToIpConverter {
public:
    explicit UrlToIpConverter(VPNContext );
    void runConvert();
    std::vector<OptionalUrl> getOptionalUrlList();

private:
    std::vector<OptionalUrl> vpnList;
    VPNContext vpnContext;

    std::vector<std::string> nsRequest(std::string url);
};

class MakeConfigurationFiles {
    MakeConfigurationFiles(VPNMode , std::vector<OptionalUrl> );
    Config MakeServerConfig(VPNMode );
    Config MakeClientConfig(VPNMode );
};

class OVPNRunner {
public:
    MakeConfigurationFiles* confFilesMaker;
    
    void RunOpenVPNServer();
    void StopOpenVPNServer();

    Config GetClientConfig();

private:
    Config serverConfig;
    Config clientConfig;
};

class VpnMsgHandler : public IHandler {
public:
    VpnMsgHandler();
    void handle(boost::asio::const_buffer ) override;
    Config reply();

private:
    void inputAnalyze();

    VPNContext convertVpnMsgToVpnContext(boost::asio::const_buffer vpnMsg);
    std::vector<OptionalUrl> convertVpnContextToVpnList(const VPNContext& );
    void setVpnContext(const VPNContext& ) {}
    void setVpnMode(const VPNMode& ) {}
    void setVpnList(const std::vector<OptionalUrl>& ) {}
    
private:
    VPNMode vpnMode;
    std::vector<OptionalUrl> vpnList;
    UrlToIpConverter* urlConverter;
    OVPNRunner* ovpnRunner;
};
