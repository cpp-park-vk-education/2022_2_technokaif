#include <iostream>
#include "handler.hpp"

#include "gtest/gtest.h"

TEST(OVPNRunnerTest, StartServerCheck) {
    OVPNRunner ovpnRunner;
    ASSERT_EQ(ovpnRunner.RunOpenVPNServer(), EXIT_SUCCESS);
}

TEST(OVPNRunnerTest, StopServerCheck) {
    OVPNRunner ovpnRunner;
    ASSERT_EQ(ovpnRunner.StopOpenVPNServer(), EXIT_SUCCESS);
}
