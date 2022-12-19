#include "server.hpp"
#include <thread>
#include <vector>

static inline constexpr int THREADS_NUM = 10;


void server_threads_spawn(boost::asio::io_context &context) {
    context.run();
}

int main(int argc, char *argv[]) {
    unsigned int port = argc > 1 ? std::stol(argv[1]) : default_port;
    boost::asio::io_context context;
    Server server(context, port);
    server.start();

    std::vector <std::thread> thread_pool;
    for (int i = 0; i < THREADS_NUM; ++i) {
        thread_pool.emplace_back(server_threads_spawn, std::ref(context));
    }

    for (std::thread &thr: thread_pool) {
        thr.join();
    }
    return 0;
}
