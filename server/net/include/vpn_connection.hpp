#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/chrono.hpp>
// #include <boost/system.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;

typedef const boost::system::error_code boost_error;
// #include <sys/types.h>
// #include "utils.hpp"

// typedef boost::shared_ptr <VpnConnection> ptr;

static const int BUFF_SIZE = 512;

class VpnConnection : public boost::enable_shared_from_this<VpnConnection> {
public:
    VpnConnection(io_context &io_context_) :
            socket_(io_context_),
            runner(OVPNRunner()) {}

    void run();

    ip::tcp::socket &getSocket();

    static boost::shared_ptr<VpnConnection> create(io_context &io_context_) {
        return boost::shared_ptr<VpnConnection>(new VpnConnection(io_context_));
    }

private:
    void readMsg();

    void handleRead(boost_error &error, size_t bytes);

    void handleMsg(IHandler *handler);

    void sendReply(ip::tcp::socket &destination);

    void connection_close();

    OVPNRunner runner;
    char read_buff[BUFF_SIZE];
    std::string write_buff;
    ip::tcp::socket socket_;
};
