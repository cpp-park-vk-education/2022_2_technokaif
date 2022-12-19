#pragma once

#include "vpn_connection.hpp"

#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <boost/bind/bind.hpp>
#include <memory>

static inline constexpr int default_port = 2020;

class Server {
public:
    Server(boost::asio::io_context &context, unsigned int port = default_port);

    void start();

private:
    void acceptConnection();

    void handleConnection(std::shared_ptr<VpnConnection> newVpnConnection,
                          const boost::system::error_code &error);

    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    size_t connections_ = 0;
};
