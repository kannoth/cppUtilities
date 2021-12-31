#include <cru/net/comm/tcp/server/server.hpp>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

server::server(int port, std::function<void(std::time_t time, std::vector<char>)> data_callback)
    : data_callback_(data_callback) {

  acceptor_ = std::make_unique<ip::tcp::acceptor>(
      io_context_, ip::tcp::endpoint(ip::tcp::v4(), port));

  this->doAccept();
}

void server::start() {}

void server::shutDown() {}

void server::detach() {}

}  // namespace tcp
}  // namespace comm
}  // namespace net
}  // namespace cru