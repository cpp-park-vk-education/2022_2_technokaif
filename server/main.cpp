#include "server.hpp"

int main(void) {
    unsigned int port = argc > 1 ? std::stol(argv[1]) : default_port;
    io_context context;
    Server server(context, port);
    server.start();
    context.run();
    return 0;
}
