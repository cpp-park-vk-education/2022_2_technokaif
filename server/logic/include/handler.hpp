#pragma once

#include <tools.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <boost/asio.hpp>
#include <json.hpp>
#include <boost/regex.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <ctime>
#include <chrono>
#include <thread>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>

const int MAX_BUFFER_SIZE = 100;

class Config {
public:
    explicit Config(std::string file_name) : _file_name(file_name) { }
    ~Config() { }

    int writeIpList(const std::string& ipList);
    int read();
    int preRead();
    std::string getConfig() { return buffer; }

private:

    std::string _file_name;
    std::fstream file_ptr;
    std::string buffer;
};

class IHandler {
public:
    virtual void handle(std::string ) = 0;
    virtual std::string reply() = 0;
};

class MakeConfigurationFiles {
public:
    void setMode(VPNMode);
    void setState(RunStatus);
    void setIpList(std::vector<std::string>);
    Config* MakeClientConfig(std::string name);
    void DeleteClientConfig(std::string name);

private:
    VPNMode vpnMode;
    RunStatus state;
    std::vector<std::string> optionalIpList;
};

class OVPNRunner {
public:
    OVPNRunner();
    ~OVPNRunner() { delete clientConfig; } 
    int RunOpenVPNServer();
    int RunOpenVPNServerWithOptions(std::vector<std::string> );
    int StopOpenVPNServer();

    std::string GetClientConfig();

private:
    void generateName();
    std::string userName;
    MakeConfigurationFiles confFilesMaker;
    Config* clientConfig;
};

class VpnMsgHandler : public IHandler {
public:
    void handle(std::string ) override;
    std::string reply() override;

private:
    void inputAnalyze(std::string );
    void logic();
    void generateName();

    void convertVpnMsgToVpnContext(std::string );
    void setVpnContext(const VPNContext& );
    void setVpnList(const std::vector<OptionalUrl>& );

private:
    VPNContext _vpnContext;
    std::vector<std::string> _ipList;
    OVPNRunner ovpnRunner;
};
