#pragma once

#include <string>

#include <boost/asio.hpp>
// #include <boost/chrono.hpp>
// #include <boost/system.hpp>
#include <boost/bind/bind.hpp>
// #include <sys/types.h>

#include <memory>

// TODO ILYA
class IHandler;

class OVPNRunner {

};
// TODO ILYA


static inline constexpr int BUFF_SIZE = 512;

class VpnConnection : public std::enable_shared_from_this<VpnConnection> {
public:
    VpnConnection(boost::asio::io_context &io_context_);

    void run(size_t *id);

    boost::asio::ip::tcp::socket &getSocket();

    std::shared_ptr<VpnConnection> getPtr() {
        return shared_from_this();
    }

    static std::shared_ptr<VpnConnection> create(boost::asio::io_context &io_context_) {
        return std::make_shared<VpnConnection>(io_context_);
    }

private:
    void readMsg();

    void handleRead(const boost::system::error_code &error, size_t bytes);

    std::string handleMsg(std::string vpnMsg);

    void sendReply();

    void closeConnection();

    void dummy(const boost::system::error_code &error, size_t bytes) {}

    // OVPNRunner runner;
    char read_buff[BUFF_SIZE];
    std::string write_buff;
    boost::asio::ip::tcp::socket socket_;

    size_t *connections_ = nullptr;
    size_t id_;
};
