#include "vpn_connection.hpp"
#include <iostream>

#define IO_BIND(a) boost::bind(&VpnConnection::a, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)

VpnConnection::VpnConnection(boost::asio::io_context &io_context_) :
// runner(OVPNRunner()),
        handler(),  // Handler INIT
        socket_(io_context_) {}

void VpnConnection::run(size_t *id) {
    id_ = *id;
    connections_ = id;
    readMsg();
}

boost::asio::ip::tcp::socket &VpnConnection::getSocket() {
    return socket_;
}

void VpnConnection::readMsg() {
    std::fill(read_buff, read_buff + BUFF_SIZE, 0);
    socket_.async_read_some(boost::asio::buffer(read_buff, BUFF_SIZE), IO_BIND(handleRead));
}

void VpnConnection::handleRead(const boost::system::error_code &error, size_t bytes) {
    if (error) {
        switch (error.value()) {
            case boost::asio::error::eof:
                closeConnection();
                break;
            default:
                std::cerr << id_ << ": INPUT READ ERROR: " << error.message() << "\n";
                break;
        }
        return;
    }
    if (bytes == 0) {
        std::cerr << id_ << ": NO INPUT GOT\n";
        return;
    }

    // std::string vpnMsg(read_buff, bytes);
    write_buff = handleMsg(std::string(read_buff, bytes));  // BLOCKING OPERATION
    sendReply();
    readMsg();
}

std::string VpnConnection::handleMsg(std::string vpnMsg) {
    std::cout << "CLIENT MESSAGE : " << vpnMsg << std::endl;
    handler.handle(vpnMsg);  // BLOCKING OPERATION
    return handler.reply();
}

void VpnConnection::sendReply() {
    async_write(socket_, boost::asio::buffer(write_buff), IO_BIND(dummy));
    write_buff.clear();
}

void VpnConnection::closeConnection() {
    std::cout << "CLIENT HAS EXITED\n";
    (*connections_)--;
    connections_ = nullptr;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
}
