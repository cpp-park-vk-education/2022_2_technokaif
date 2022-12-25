#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include "server.hpp"

#include "gtest/gtest.h"

#define PORT 2020

TEST(ServerTest, DISABLED_Test1) {
    boost::asio::io_context context;
    Server server(context, PORT);
    server.start();

    std::string nc_exec1 = "nc -N 0.0.0.0 " + std::to_string(PORT);
    std::string echo_exec1 = "echo request__1";
    boost::process::ipstream is1;
    boost::process::pipe pipe1;
    boost::process::child echo1(echo_exec1, boost::process::std_out > pipe1);
    boost::process::child nc1(nc_exec1, boost::process::std_in < pipe1, boost::process::std_out > is1);

    std::string nc_exec2 = "nc -N 0.0.0.0 " + std::to_string(PORT);
    std::string echo_exec2 = "echo request__2";
    boost::process::ipstream is2;
    boost::process::pipe pipe2;
    boost::process::child echo2(echo_exec2, boost::process::std_out > pipe2);
    boost::process::child nc2(nc_exec2, boost::process::std_in < pipe2, boost::process::std_out > is2);

    echo1.wait();
    echo2.wait();
    while(nc1.running() || nc2.running()) {
        context.poll();
    }
    nc1.wait();
    nc2.wait();

    std::string answer;
    std::getline(is1, answer);
    ASSERT_EQ(answer, "request__1");

    std::getline(is2, answer);
    ASSERT_EQ(answer, "request__2");
}

class SimpleSyncClientPool {
    size_t num;
    boost::asio::io_context client_context;
    std::vector<boost::asio::ip::tcp::socket> socket_pool;
    std::string ip = "0.0.0.0";

public:
    SimpleSyncClientPool(size_t num) : num(num), client_context()  {
        for (size_t i = 0; i < num; ++i) {
            socket_pool.emplace_back(client_context);
        }
    }
    void connectAll() {
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), PORT);
        for (auto &sock : socket_pool) {
            sock.connect(ep);
        }
    }

    void sendAll(std::vector<std::string> requests) {
        for (size_t i = 0; i < num; ++i) {
            socket_pool[i].send(boost::asio::buffer(requests[i]));
        }
    }

    std::vector<std::string> getAll(int receive_size) {
        std::vector<std::string> input(num);

        for (size_t i = 0; i < num; ++i) {
            input[i].resize(receive_size);
            socket_pool[i].receive(boost::asio::buffer(input[i]));
        }
        return input;
    }

    void closeAll() {
        for (auto &sock : socket_pool) {
            sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        }
    }
};

TEST(ServerTest, DISABLED_Test2) {
    int clients_num = 1000;

    boost::asio::io_context server_context;
    Server server(server_context, PORT);
    server.start();

    SimpleSyncClientPool client_pool(clients_num);
    client_pool.connectAll();

    std::vector<std::string> requests;
    static char randomm[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
                             'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k',
                             'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '1',
                             '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    for (int i = 0; i < clients_num; ++i) {
        std::string result;
        for (size_t i = 0; i < 10; ++i)
            result += randomm[std::rand() % 36];
        requests.push_back(result);
    }

    client_pool.sendAll(requests);
    server_context.poll();

    auto responses = client_pool.getAll(10);

    for(int i = 0; i < clients_num; ++i) {
        ASSERT_EQ(responses[i], requests[i]);
    }

    client_pool.closeAll();
    server_context.poll();
}
