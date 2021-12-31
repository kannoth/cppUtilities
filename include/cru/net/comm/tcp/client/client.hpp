#ifndef CRU_NET_COMM_TCP_CLIENT_HPP
#define CRU_NET_COMM_TCP_CLIENT_HPP

#include <cru/net/comm/tcp/client/api/i_client.hpp>

#include <boost/asio.hpp>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

class client : public api::i_client {
  enum { max_length = 1024 };
public:
  client(const std::string& endpoint, int port);
  virtual void connect() override;
  virtual void disconnect() override;
  virtual void send(const std::vector<char> data) override;

  private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string end_point_;
    int port_;
    char request_buffer_[max_length];
};

}
}
}
}
#endif