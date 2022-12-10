#include "network/include/client.h"

int main() {
    boost::asio::io_context context;
    std::string ip = "127.0.0.1";
    unsigned int port = 80;

    // std::string ip = "51.250.94.232";
    // unsigned int port = 2020;

    Client client(context, ip, port);
    client.getVPNContext();  // from console
    client.connect();

    while (!client.isStateStop()) {
        client.sendData();
        client.getData();
        client.getVPNContext();
        client.connect();
    }
    client.sendData();
    client.stopConnection();

    return 0;
}
