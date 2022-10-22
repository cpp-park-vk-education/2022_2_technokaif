#include <iostream>

#include "gtest/gtest.h"

#include "logic.hpp"

TEST(FactorialTest, returnTest) {
    ASSERT_EQ(fact(0), 1);
    ASSERT_EQ(fact(5), 120);
}