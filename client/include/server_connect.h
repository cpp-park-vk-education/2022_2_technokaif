#pragma once

#include "tools/utils.h"

enum VPNMode {
    runTotal,
    runOptional,
    stopped
};

struct VPNContext {
    VPNMode state;
    std::vector<std::string> urlList; 
};

class IOVPNClient {
 public:
    virtual void runOvpn() = 0;
    virtual void stopOvpn() = 0;
};

class OVPNClient : public IOVPNClient {
 public:
    void runOvpn();
    void stopOvpn();
 private:
    std::string configFileName;

    void execOVPN();
};

class Client {
 public:
    void connect();
    void setVpnContext(VPNContext context);
    void handleWrite();
    void handleRead();
    void asyncReadMsg();
    void asyncWrite();
 private:
    static const int BUFFER_SIZE = 512;

    char _msg[BUFFER_SIZE];
    OVPNClient _ovpn;
    VPNContext _context;

    void _inputAnalysis();
    void _ovpnClientStart();
    void _ovpnClientStop();
};
