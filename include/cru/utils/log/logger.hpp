#ifndef CRU_UITLS_LOG_LOGGER_HPP
#define CRU_UITLS_LOG_LOGGER_HPP

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>

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
  severity severity_;

 public:
  logger(const std::string& t_entity, std::ostream& t_stream,
         severity t_severity)
      : m_entity(t_entity), m_stream(t_stream), severity_(t_severity) {}

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
  void warns(Args&&... t_args) noexcept;

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
#ifdef PRINT_TO_STD_OUT
    if
      constexpr(!sizeof...(Args)) m_stream << t_arg;
    else {
      m_stream << t_arg << ' ';
      print(std::forward<Args>(t_args)...);
      fflush(stdout);
    }
#else
    if
      constexpr(!sizeof...(Args)) fmt::print(t_arg);
    else {
      fmt::print(t_arg);
      fmt::print(" ");
      print(std::forward<Args>(t_args)...);
    }
#endif
  }

  std::string timestamp() {
    std::ostringstream oss;
    auto now{
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    oss << std::put_time(localtime(&now), "%F %T");
    return "[" + oss.str() + "]";
  }
};

template <typename... Args>
inline void logger::infos(Args&&... t_args) noexcept {
  if (severity_ >= severity::info) return;
#ifdef PRINT_TO_STD_OUT
  log_("[INFO]", std::forward<Args>(t_args)...);
#else
  fmt::print(fg(fmt::color::green), timestamp() + "[INFO]");
  log_("", std::forward<Args>(t_args)...);
#endif
}

template <typename... Args>
inline void logger::traces(Args&&... t_args) noexcept {
  if (severity_ >= severity::trace) return;
#ifdef PRINT_TO_STD_OUT
  log_("[TRACE]", std::forward<Args>(t_args)...);
#else
  fmt::print(fg(fmt::color::yellow), timestamp() + "[TRACE]");
  log_("", std::forward<Args>(t_args)...);
#endif
}

template <typename... Args>
inline void logger::debugs(Args&&... t_args) noexcept {
  if (severity_ >= severity::debug) return;
#ifdef PRINT_TO_STD_OUT
  log_("[DEBUG]", std::forward<Args>(t_args)...);
#else
  fmt::print(fg(fmt::color::deep_sky_blue), timestamp() + "[DEBUG]");
  log_("", std::forward<Args>(t_args)...);
#endif
}

template <typename... Args>
inline void logger::errors(Args&&... t_args) noexcept {
  if (severity_ >= severity::error) return;
#ifdef PRINT_TO_STD_OUT
  log_("[ERROR]", std::forward<Args>(t_args)...);
#else
  fmt::print(fg(fmt::color::red), timestamp() + "[ERROR]");
  log_("", std::forward<Args>(t_args)...);
#endif
}

template <typename... Args>
inline void logger::warns(Args&&... t_args) noexcept {
  if (severity_ >= severity::warn) return;
#ifdef PRINT_TO_STD_OUT
  log_("[WARNING]", std::forward<Args>(t_args)...);
#else
  fmt::print(fg(fmt::color::orange), timestamp() + "[WARNING]");
  log_("", std::forward<Args>(t_args)...);
#endif
}

template <typename... Args>
inline void logger::fatals(Args&&... t_args) noexcept {
  if (severity_ >= severity::fatal) return;
#ifdef PRINT_TO_STD_OUT
  log_("[FATAL]", std::forward<Args>(t_args)...);
#else
  fmt::print(fg(fmt::color::hot_pink), timestamp() + "[FATAL]");
#endif
  log_("", std::forward<Args>(t_args)...);
}

template <typename Arg, typename... Args>
inline void logger::log_(Arg&& t_severity, Args&&... t_args) noexcept {
#ifdef PRINT_TO_STD_OUT
  print(timestamp());
  print(t_severity);
#endif
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
