namespace cru {
namespace net {
namespace comm {
namespace tcp {
namespace api {

class i_server {
 public:
  virtual ~i_server() = default;
  virtual void start() = 0;
  virtual void shutDown() = 0;
  virtual void detach() = 0;
};

}  // namespace api
}  // namespace tcp
}  // namespace comm
}  // namespace net
}  // namespace cru