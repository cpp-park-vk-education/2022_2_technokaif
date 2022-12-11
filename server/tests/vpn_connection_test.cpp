#include <iostream>
#include <memory>
#include "vpn_connection.hpp"
#include "server.hpp"

#include "gtest/gtest.h"

TEST(VpnConnectionTest, StartConnectionCheck) {
    boost::asio::io_context context;
    size_t connections = 0;

    std::shared_ptr<VpnConnection> conn1_ptr = VpnConnection::create(context);
    std::shared_ptr<VpnConnection> conn2_ptr = VpnConnection::create(context);

    connections++;
    conn1_ptr->run(&connections);

    connections++;
    conn2_ptr->run(&connections);

    conn1_ptr.reset();
    conn2_ptr.reset();
}
