#include "tools.h"
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
public:
    MakeConfigurationFiles(VPNMode vpnMode_, std::vector<OptionalUrl> optionalUrlList_)
            : vpnMode(vpnMode_), optionalUrlList(optionalUrlList_) { }
    Config MakeServerConfig();
    Config MakeClientConfig();

private:
    VPNMode vpnMode;
    std::vector<OptionalUrl> optionalUrlList;
};

class OVPNRunner {
public:
    OVPNRunner();
    
    void RunOpenVPNServer();
    void StopOpenVPNServer();

    Config GetClientConfig();
    Config GetServerConfig();

private:
    MakeConfigurationFiles* confFilesMaker;
    Config serverConfig;
    Config clientConfig;
};

class VpnMsgHandler : public IHandler {
public:
    VpnMsgHandler(OVPNRunner& runner) : ovpnRunner(runner) { }
    void handle(boost::asio::const_buffer ) override;
    Config reply();

private:
    void inputAnalyze();

    VPNContext convertVpnMsgToVpnContext(boost::asio::const_buffer vpnMsg);
    std::vector<OptionalUrl> convertVpnContextToVpnList(const VPNContext& );
    void setVpnContext(const VPNContext& );
    void setVpnMode(const VPNMode& );
    void setVpnList(const std::vector<OptionalUrl>& );

private:
    VPNMode vpnMode;
    VPNContext vpnContext;
    std::vector<OptionalUrl> vpnList;
    UrlToIpConverter* urlConverter;
    OVPNRunner& ovpnRunner;
};
