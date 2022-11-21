#pragma once

#include "vpn_connection.hpp"

#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/system.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

typedef const boost::system::error_code boost_error;
static const int default_port = 0;

class Server {
public:
    Server(boost::asio::io_context &context, unsigned int port);

    void start();

private:
    void acceptConnection();

    void handleConnection(boost::shared_ptr<VpnConnection> newVpnConnection,
                          boost_error &error);
    // void clients_status(boost_error &error);

    io_context &io_context_;
    ip::tcp::acceptor acceptor_;
    size_t connections;

    // Client::clients_map clients;
    // steady_timer timer;
};
