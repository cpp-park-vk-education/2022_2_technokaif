#include <iostream>
#include "handler.hpp"

#include "gmock/gmock.h"

class MockHandler : public IHandler {
public:
    MOCK_METHOD1(handle, void(std::string buffer));
    MOCK_METHOD0(reply, std::string());
};

TEST(ServerHandlerTest, HandlerStartCheck) {
    MockHandler handler;
    std::string buffer = "";
    EXPECT_CALL(handler, handle(buffer)).Times(1);

    handler.handle(buffer);
}

TEST(ServerHandlerTest, ReplyCheck) {
    MockHandler handler;
    EXPECT_CALL(handler, reply).Times(1);

    handler.reply();
}
