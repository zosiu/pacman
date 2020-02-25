#pragma once

#ifndef BE6D9ED6_2134_3B09_70A9_4E042FB390B1
#define BE6D9ED6_2134_3B09_70A9_4E042FB390B1

#include "../Event.hpp"

namespace engine {

class WindowResizedEvent : public Event {
public:
  static EventType get_static_type();

  WindowResizedEvent(uint16_t width, uint16_t height);

  std::string get_name() const override;
  EventType get_event_type() const override;

  uint16_t get_width() const;
  uint16_t get_height() const;

private:
  uint16_t width;
  uint16_t height;
};

} // namespace engine

#endif /* BE6D9ED6_2134_3B09_70A9_4E042FB390B1 */
