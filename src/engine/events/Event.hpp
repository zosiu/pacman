#pragma once

#ifndef DEE5B893_3134_3B08_D6BE_47647F5923DB
#define DEE5B893_3134_3B08_D6BE_47647F5923DB

namespace engine {

enum class EventType { None = 0, WindowClosed };

class Event {
public:
  virtual std::string get_name() const = 0;
  virtual EventType get_event_type() const = 0;

  virtual ~Event() = default;
};

inline std::ostream &operator<<(std::ostream &os, const Event &event) { return os << event.get_name(); }

} // namespace engine

#endif /* DEE5B893_3134_3B08_D6BE_47647F5923DB */
