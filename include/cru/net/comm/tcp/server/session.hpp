#ifndef CRU_NET_COMM_TCP_SESSION_HPP
#define CRU_NET_COMM_TCP_SESSION_HPP

#include <boost/asio.hpp>
#include <cru/net/comm/tcp/server/api/i_server.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

namespace ip = boost::asio::ip;

// Implementation copied from
// https://www.boost.org/doc/libs/1_77_0/doc/html/boost_asio/example/cpp11/echo/async_tcp_echo_server.cpp
class session : public std::enable_shared_from_this<session> {
 public:
  session(ip::tcp::socket socket) : socket_(std::move(socket)) {}

  void start() { doRead(); }

 private:
  void doRead() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
          if (!ec) {
            doWrite(length);
          }
        });
  }

  void doWrite(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            doRead();
          }
        });
  }

  ip::tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

}
}
}
}

#endif /* CRU_NET_COMM_TCP_SESSION_HPP */