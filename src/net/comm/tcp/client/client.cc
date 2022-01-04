#include <cru/net/comm/tcp/client/client.hpp>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

client::client(const std::string& end_point, int port)
    : socket_(io_context_), end_point_(end_point), port_(port) {}

// TODO : Handle exceptions
void client::connect() {
  boost::asio::ip::tcp::resolver resolver(io_context_);
  boost::asio::ip::tcp::resolver::query query(end_point_,
                                              std::to_string(port_));
  boost::asio::connect(socket_, resolver.resolve(query));
}

void client::disconnect() {}

void client::send(const std::string& data) {

  boost::asio::write(socket_,
                     boost::asio::buffer(data, data.size()));
}
}
}
}
}