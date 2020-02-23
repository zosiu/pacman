#pragma once

#ifndef E3A2FBD7_D134_3B08_DA49_F9BE8AEB3158
#define E3A2FBD7_D134_3B08_DA49_F9BE8AEB3158

#include "../Event.hpp"

namespace engine {

class WindowClosedEvent : public Event {
public:
  static EventType get_static_type();
  std::string get_name() const override;
  EventType get_event_type() const override;

  WindowClosedEvent() = default;
};

} // namespace engine

#endif /* E3A2FBD7_D134_3B08_DA49_F9BE8AEB3158 */
