
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
  std::mutex mutex_;
  std::string server_rx_data_;

  void SetUp() override {
    server_ = new server(port_, [&](std::time_t time, const std::string& data) {
      std::lock_guard<std::mutex> guard(mutex_);
      cond_var_.notify_one();
      server_rx_data_ = data;
    });

    client_ = new client(address_, port_);

    server_thread_ = std::make_unique<std::thread>([&]() { server_->start(); });

    server_thread_->detach();
  }

  void TearDown() override {
    // server_thread_->join();
  }
};

TEST_F(ServerTest, SendData) {
  std::string test_string("Hello CRU");
  EXPECT_EQ(std::string(), server_rx_data_);

  client_->connect();
  client_->send(test_string);

  std::unique_lock<std::mutex> lock(mutex_);
  cond_var_.wait(lock);
  EXPECT_EQ(test_string, server_rx_data_),

  server_->shutDown();
}
}
