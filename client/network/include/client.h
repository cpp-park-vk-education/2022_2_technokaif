#include "tools.h"
#include <string>

class IOpenVPNClient {
public:
    virtual void runOpenVPN() = 0;
    virtual void stopOpenVPN() = 0;
};

class OpenVPNClient : virtual public IOpenVPNClient {
private:
    std::string _configFileName;
    void execOpenVPN();

public:
    virtual void runOpenVPN() override;
    virtual void stopOpenVPN() override;
};

class Client {
private:
    static const int BUFFER_SIZE = 512;
    char msg[BUFFER_SIZE];
    OpenVPNClient oVPNClient;
    VPNContext context;

    void _onContext();
    void _asyncReadMsg();  // может прийти конфиг или таймаут
    void _handleRead();
    void _inputAnalysis();

    void _asincWrite();
    void _handleWrite();

public:
    void setVPNContext(VPNContext);
    void connect();
};