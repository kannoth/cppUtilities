
#ifndef CRU_NET_COMM_TCP_I_CLIENT_HPP
#define CRU_NET_COMM_TCP_I_CLIENT_HPP

#include <vector>

namespace cru {
namespace net {
namespace comm {
namespace tcp {
namespace api {

class i_client {
public:
  virtual ~i_client() = default;
  virtual void connect() = 0;
  virtual void disconnect() = 0;
  virtual void send(const std::vector<char> data);
};

}
}
}
}
}

#endif /* CRU_NET_COMM_TCP_I_CLIENT_HPP */