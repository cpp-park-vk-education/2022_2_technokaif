#include "vpn_connection.hpp"

VpnConnection::VpnConnection(io_context &io_context_) :
            socket_(io_context_),
            runner(OVPNRunner()) {}

void VpnConnection::run() {

}

ip::tcp::socket &VpnConnection::getSocket() {

}

void VpnConnection::readMsg() {

}

void VpnConnection::sendReply(ip::tcp::socket &destination) {

}

void VpnConnection::handleMsg(boost_error &error, size_t bytes, IHandler *handler) {

}

void VpnConnection::connection_close() {

}
