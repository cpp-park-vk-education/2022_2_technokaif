#pragma once

#include "vpn_connection.hpp"

class Server {
public:
    Server(boost::asio::io_context &context, unsigned int port);

    void start();

private:
    void acceptConnection();

    void handleConnection(boost::shared_ptr<VpnConnection> newVpnConnection,
                          boost_error &error);
    // void clients_status(boost_error &error);

    io_context &io_context;
    ip::tcp::acceptor acceptor;
    static size_t connections = 0;
    // Client::clients_map clients;
    // steady_timer timer;
};
