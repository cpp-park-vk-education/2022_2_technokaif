#include "server.hpp"

Server::Server(boost::asio::io_context &context, unsigned int port) :
        io_context_(context),
        acceptor_(context, ip::tcp::endpoint(ip::tcp::v4(), port)),
        connections(0) {

}

void Server::start() {

}

void Server::acceptConnection() {

}

void Server::handleConnection(boost::shared_ptr <VpnConnection> newVpnConnection,
                              boost_error &error) {

}
