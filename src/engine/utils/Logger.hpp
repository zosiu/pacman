#pragma once

#ifndef A00B3F40_2134_3B0E_163E_BE8C3F77F490
#define A00B3F40_2134_3B0E_163E_BE8C3F77F490

#include <spdlog/spdlog.h>

namespace engine {

class Logger {
public:
  static void init(const std::string &filename = "engine.log");

  inline static std::shared_ptr<spdlog::logger> &instance() { return logger_instance; }

private:
  static std::shared_ptr<spdlog::logger> logger_instance;
};

} // namespace engine

#define LOG_TRACE(...) ::engine::Logger::instance()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::engine::Logger::instance()->info(__VA_ARGS__)
#define LOG_WARN(...) ::engine::Logger::instance()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::engine::Logger::instance()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::engine::Logger::instance()->critical(__VA_ARGS__)

#endif /* A00B3F40_2134_3B0E_163E_BE8C3F77F490 */
