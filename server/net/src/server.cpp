#include "server.hpp"
#include <iostream>

// #define SV_BIND(handle)  boost::bind(&Server::handle, this, connection, std::placeholders::error)
// #define NOCL_BIND(handle)  boost::bind(&Server::handle, this, placeholders::error)

Server::Server(boost::asio::io_context &context, unsigned int port) :
        io_context_(context),
        acceptor_(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

void Server::start() {
    acceptConnection();
}

void Server::acceptConnection() {
    std::shared_ptr <VpnConnection> connection = VpnConnection::create(io_context_);
    acceptor_.async_accept(connection->getSocket(), boost::bind(&Server::handleConnection,
                                                                this,
                                                                connection,
                                                                boost::asio::placeholders::error));
}

void Server::handleConnection(std::shared_ptr <VpnConnection> newVpnConnection,
                              const boost::system::error_code &error) {
    if (error) {
        std::cerr << "CONNECTION ERROR " << error.message() << "\n";
        acceptConnection();
        return;
    }
    std::cout << "CLIENT CONNECTED\n";
    connections_++;  // TODO vpn connect should connections--
    newVpnConnection->run(&connections_);  // RUN
    acceptConnection();
}
