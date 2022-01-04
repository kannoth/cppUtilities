
#ifndef CRU_NET_COMM_TCP_SESSION_HPP
#define CRU_NET_COMM_TCP_SESSION_HPP

#include <cru/net/comm/tcp/server/api/i_server.hpp>
#include <boost/asio.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <chrono>
#include <vector>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

namespace ip = boost::asio::ip;

// Implementation copied from
// https://www.boost.org/doc/libs/1_77_0/doc/html/boost_asio/example/cpp11/echo/async_tcp_echo_server.cpp
class session : public std::enable_shared_from_this<session> {
 public:

  session(ip::tcp::socket socket,
          std::function<void(std::time_t, const std::string&)>
              session_callback)
      : socket_(std::move(socket)), session_callback_(session_callback) {}

  void start() { doRead(); }

 private:
  void doRead() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
          if (!ec) {
            using namespace std::chrono;
            system_clock::time_point point = system_clock::now();
            auto time = system_clock::to_time_t(point);
            
            if(session_callback_)
              session_callback_(time, std::string(data_, length));
          }
        });
  }

  ip::tcp::socket socket_;
  std::function<void(std::time_t time, const std::string&)> session_callback_;
  enum { max_length = 1024 };
  char data_[max_length];
};
}
}
}
}

#endif /* CRU_NET_COMM_TCP_SESSION_HPP */
