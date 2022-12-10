#pragma once

#include <tools.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <boost/asio.hpp>
#include <json.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
// #include <boost/log.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>

// using boost::filesystem;
// namespace json = nlohman::json;

class Config {
public:
    Config();
    explicit Config(std::string fileName);
    Config(const Config&);
    ~Config();

    void write(const std::string& buffer);
    std::string& read();

private:
    std::fstream file_ptr;
    std::string buffer;
};

class IHandler {
public:
    virtual void handle(std::string ) = 0;
    virtual Config reply() = 0;
};

class UrlToIpConverter {
public:    
    std::vector<OptionalUrl> getOptionalUrlList(VPNContext vpnContext_);

private:
    void runConvert();
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
    
    int RunOpenVPNServer();
    int StopOpenVPNServer();

    Config GetClientConfig();
    Config GetServerConfig();

private:
    MakeConfigurationFiles* confFilesMaker;
    Config serverConfig;
    Config clientConfig;
};

class VpnMsgHandler : public IHandler {
public:
    explicit VpnMsgHandler(OVPNRunner& runner) : ovpnRunner(runner) { }
    void handle(std::string ) override;
    Config reply() override;

private:
    void inputAnalyze(std::string );

    void convertVpnMsgToVpnContext(std::string );
    void convertVpnContextToVpnList();
    void setVpnContext(const VPNContext& );
    void setVpnList(const std::vector<OptionalUrl>& );

private:
    VPNContext _vpnContext;
    std::vector<OptionalUrl> _vpnList;
    UrlToIpConverter urlConverter;
    OVPNRunner& ovpnRunner;
};
