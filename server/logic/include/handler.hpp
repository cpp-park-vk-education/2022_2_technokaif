#pragma once

#include <tools.h>
#include <fstream>
#include <boost/asio.hpp>

const int BUFF_SIZE = 512;

class Config {
public:
    Config();
    explicit Config(std::string fileName);
    Config(const Config&);
    ~Config();

    void write(const std::string& buffer);
    std::string& read();

private:
    std::ifstream file_ptr;
    std::string buffer;
};

class IHandler {
public:
    virtual void handle(char[BUFF_SIZE] ) = 0;
    virtual Config reply() = 0;
};

class UrlToIpConverter {
public:
    explicit UrlToIpConverter(VPNContext vpnContext_) : vpnContext(vpnContext_) { }
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
    void handle(char[BUFF_SIZE] ) override;
    Config reply();

private:
    void inputAnalyze(char[BUFF_SIZE] );

    VPNContext convertVpnMsgToVpnContext(char vpnMsg[]);
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
