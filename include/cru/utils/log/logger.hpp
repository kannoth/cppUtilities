#ifndef CRU_UITLS_LOG_LOGGER_HPP
#define CRU_UITLS_LOG_LOGGER_HPP

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <vector>

namespace cru {
namespace utils {

class logger {
 public:
  enum class severity : unsigned {
    all,
    trace,
    debug,
    info,
    warn,
    error,
    fatal,
    off
  };

 private:
  std::string m_entity;
  std::ostream& m_stream;
  severity m_severity;

 public:
  logger(const std::string& t_entity, std::ostream& t_stream,
         severity t_severity)
      : m_entity(t_entity), m_stream(t_stream), m_severity(t_severity) {}

  logger(const std::string& t_entity, severity t_severity)
      : logger(t_entity, std::cout, t_severity) {}

  logger(const std::string& t_entity)
      : logger(t_entity, std::cout, severity::all) {}

  virtual ~logger() = default;

  void info(const std::string& t_message) { infos(t_message); }

  void trace(const std::string& t_message) { traces(t_message); }

  void debug(const std::string& t_message) { debugs(t_message); }

  void error(const std::string& t_message) { errors(t_message); }

  void fatal(const std::string& t_message) { fatals(t_message); }

  template <typename... Args>
  void infos(Args&&... t_args) noexcept;

  template <typename... Args>
  void traces(Args&&... t_args) noexcept;

  template <typename... Args>
  void debugs(Args&&... t_args) noexcept;

  template <typename... Args>
  void errors(Args&&... t_args) noexcept;

  template <typename... Args>
  void fatals(Args&&... t_args) noexcept;

  template <typename Arg, typename... Args>
  void log_(Arg&& t_severity, Args&&... t_args) noexcept;

  template <typename... Args>
  void dump(Args&&... t_args) noexcept;

  static logger entity();
  static logger entity(const std::string& t_entity);

 private:
  template <typename Arg, typename... Args>
  constexpr void print(Arg&& t_arg, Args&&... t_args) noexcept {
    if
      constexpr(!sizeof...(Args)) m_stream << t_arg;
    else {
      m_stream << t_arg << ' ';
      print(std::forward<Args>(t_args)...);
      fflush(stdout);
    }
  }

  std::string timestamp();
};

template <typename... Args>
inline void logger::infos(Args&&... t_args) noexcept {
  log_("[INFO]", std::forward<Args>(t_args)...);
}

template <typename... Args>
inline void logger::traces(Args&&... t_args) noexcept {
  log_("[TRACE]", std::forward<Args>(t_args)...);
}

template <typename... Args>
inline void logger::debugs(Args&&... t_args) noexcept {
  log_("[DEBUG]", std::forward<Args>(t_args)...);
}

template <typename... Args>
inline void logger::errors(Args&&... t_args) noexcept {
  log_("[ERROR]", std::forward<Args>(t_args)...);
}

template <typename... Args>
inline void logger::fatals(Args&&... t_args) noexcept {
  log_("[FATAL]", std::forward<Args>(t_args)...);
}

template <typename Arg, typename... Args>
inline void logger::log_(Arg&& t_severity, Args&&... t_args) noexcept {
  print(timestamp());
  print(t_severity);
  print("[");
  print(m_entity);
  print("] ");
  print(std::forward<Args>(t_args)...);
  print("\n");
}

template <typename... Args>
inline void logger::dump(Args&&... t_args) noexcept {
  print(std::forward<Args>(t_args)...);
  print("\n");
}
}
}
#endif