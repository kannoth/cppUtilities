#include <cru/net/comm/tcp/server/server.hpp>

namespace cru {
namespace net {
namespace comm {
namespace tcp {

server::server(
    int port,
    std::function<void(std::time_t, const std::string&)> data_callback)
    : data_callback_(data_callback),
      logger_(utils::logger("cru_tcp_server", utils::logger::severity::all)),
      is_running(true) {
  acceptor_ = std::make_unique<ip::tcp::acceptor>(
      io_context_, ip::tcp::endpoint(ip::tcp::v4(), port));

  logger_.info("Started");
  this->doAccept();
}

void server::start() {
  while (!is_running.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    io_context_.stop();
  }
  std::thread ioc_thread([&]() { io_context_.run(); });

  ioc_thread.join();
}

void server::shutDown() { 
      logger_.trace("Shutting down ...");
      is_running.store(false); }

void server::detach() {}

}  // namespace tcp
}  // namespace comm
}  // namespace net
}  // namespace cru