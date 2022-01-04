
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>

#include <gtest/gtest.h>
#include <cru/net/comm/tcp/server/server.hpp>
#include <cru/net/comm/tcp/client/client.hpp>

namespace tcp_server_test {

using namespace cru::net::comm::tcp;

class ServerTest : public ::testing::Test {
 protected:
  api::i_server* server_;
  api::i_client* client_;

  const int port_ = 5000;
  const char* address_ = "localhost";

  std::unique_ptr<std::thread> server_thread_;
  std::condition_variable cond_var_;
  bool booted_ = false;
  std::mutex mutex_;
  std::string server_rx_data_;

  void SetUp() override {
    server_ = new server(port_, [&](std::time_t time, const std::string& data) {
      server_rx_data_ = data;
    });

    client_ = new client(address_, port_);

    server_thread_ = std::make_unique<std::thread>(
      [&]() { server_->start(); });
  }

  void TearDown() override {
    server_thread_->join();
  }
};

TEST_F(ServerTest, SendData) {
  std::string test_string("Hello CRU");
  EXPECT_EQ(std::string(), server_rx_data_);

  client_->send("Hello Server");

  EXPECT_EQ(test_string, server_rx_data_),

  server_->shutDown();
}
}
