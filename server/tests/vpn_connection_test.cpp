#include <iostream>
#include <shared_ptr>
#include "vpn_connection.hpp"

#include "gtest/gtest.h"

TEST(VpnConnectionTest, StartConnectionCheck) {
    boost::asio::io_context context;
    size_t connections = 0;

    std::shared_ptr<VpnConnection> conn1_ptr = VpnConnection::create(context);
    std::shared_ptr<VpnConnection> conn2_ptr = VpnConnection::create(context);

    conn1_ptr->run(&connections);
    conn2_ptr->run(&connections);

    ASSERT_EQ(connections, 2);

    conn1_ptr.reset();
    ASSERT_EQ(connections, 1);

    conn2_ptr.reset();
    ASSERT_EQ(connections, 0);
}
