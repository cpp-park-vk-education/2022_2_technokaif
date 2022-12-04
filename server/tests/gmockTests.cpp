#include <iostream>
#include "handler.hpp"

#include "gmock/gmock.h"

class MockHandler : public IHandler {
public:
    MOCK_METHOD1(handle, void(char* buffer));
    MOCK_METHOD0(reply, Config());
};

TEST(ServerHandlerTest, HandlerStartCheck) {
    MockHandler handler;
    char buffer[BUFF_SIZE];
    EXPECT_CALL(handler, handle(buffer)).Times(1);

    handler.handle(buffer);
    // OVPNRunner ovpnRunner;
    // VpnMsgHandler realHandler(ovpnRunner);
    // realHandler.handle(buffer);
}

TEST(ServerHandlerTest, ReplyCheck) {
    MockHandler handler;
    EXPECT_CALL(handler, reply).Times(1);

    handler.reply();
    // OVPNRunner ovpnRunner;
    // VpnMsgHandler realHandler(ovpnRunner);
    // realHandler.reply();
}
