#ifndef CRU_NET_COMM_TCP_SERVER_HPP
#define CRU_NET_COMM_TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include <cru/net/comm/tcp/server/api/i_server.hpp>
#include <cru/net/comm/tcp/server/session.hpp>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

class server final : public api::i_server {
 public:
  server(
      int port,
      std::function<void(std::time_t time, std::vector<char>)> data_callback);
  ~server() = default;

  virtual void start() override;
  virtual void shutDown() override;
  virtual void detach() override;

 private:
  void doAccept() {
    acceptor_->async_accept(
        [this](boost::system::error_code ec, ip::tcp::socket socket) {
          if (!ec) {
            std::make_shared<session>(std::move(socket), data_callback_)->start();
          }

          doAccept();
        });
  }

 private:
  std::function<void(std::time_t time, std::vector<char>)> data_callback_;
  boost::asio::io_context io_context_;
  std::unique_ptr<ip::tcp::acceptor> acceptor_;
};

}  // namespace tcp
}  // namespace comm
}  // namespace net
}  // namespace cru

#endif /* CRU_NET_COMM_TCP_SERVER_HPP */