#include "vpn_connection.hpp"

/*
#define SV_BIND(a)  boost::bind(&Server::a, this, new_client, placeholders::error)
#define NOCL_BIND(a)  boost::bind(&Server::a, this, placeholders::error)
#define IO_BIND(a)  boost::bind(&Client::a, shared_from_this(), placeholders::error, placeholders::bytes_transferred)
*/

VpnConnection::VpnConnection(io_context &io_context_) :
        runner(OVPNRunner()),
        socket_(io_context_) {}

int VpnConnection::run() {

    return 0;
}

ip::tcp::socket &VpnConnection::getSocket() {
    return socket_;
}

void VpnConnection::readMsg() {
    /*std::fill(read_buff, read_buff + sizeof(read_buff), 0);
    socket_.async_read_some(buffer(read_buff, sizeof(read_buff)), IO_BIND(handleRead));*/
}

void VpnConnection::handleRead(boost_error &error, size_t bytes) {
    // TODO проверка ошибок
    /*Handler *handler = new Handler(runner);
    handleMsg(handler);*/
}

void VpnConnection::sendReply(ip::tcp::socket &destination) {

}

void VpnConnection::handleMsg(IHandler *handler) {

}

void VpnConnection::connection_close() {

}
