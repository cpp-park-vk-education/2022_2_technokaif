#include <iostream>
#include "vpn_connection.hpp"

#include "gtest/gtest.h"

TEST(VpnConnectionTest, StartConnectionCheck) {
    boost::asio::io_context context;
    VpnConnection conn(context);
    ASSERT_EQ(conn.run(), EXIT_SUCCESS);
}
