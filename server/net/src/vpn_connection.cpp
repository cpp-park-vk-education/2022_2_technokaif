#include "vpn_connection.hpp"

#define SV_BIND(a)  boost::bind(&Server::a, this, new_client, placeholders::error)
#define NOCL_BIND(a)  boost::bind(&Server::a, this, placeholders::error)
#define IO_BIND(a)  boost::bind(&Client::a, shared_from_this(), placeholders::error, placeholders::bytes_transferred)

VpnConnection::VpnConnection(io_context &io_context_) :
            socket_(io_context_),
            runner(OVPNRunner()) {}

void VpnConnection::run() {

}

ip::tcp::socket &VpnConnection::getSocket() {

}

void VpnConnection::readMsg() {

    std::fill(read_buff, read_buff + sizeof(read_buff), 0);
    socket_.async_read_some(buffer(read_buff, sizeof(read_buff)), IO_BIND(handleRead));
}

void VpnConnection::handleRead(boost_error &error, size_t bytes) {
    // TODO ��������� ������
    IHandler *handler = new IHandler(runner);
    handlerMsg(handler);
}

void VpnConnection::sendReply(ip::tcp::socket &destination) {

}

void VpnConnection::handleMsg(IHandler *handler) {

}

void VpnConnection::connection_close() {

}
