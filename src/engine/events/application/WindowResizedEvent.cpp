#include "WindowResizedEvent.hpp"

namespace engine {

EventType WindowResizedEvent::get_static_type() { return EventType::WindowResized; }

WindowResizedEvent::WindowResizedEvent(uint16_t width, uint16_t height) : width(width), height(height) {}

EventType WindowResizedEvent::get_event_type() const { return get_static_type(); }

uint16_t WindowResizedEvent::get_width() const { return width; }
uint16_t WindowResizedEvent::get_height() const { return height; }

std::string WindowResizedEvent::get_name() const {
  std::stringstream ss;
  ss << "[application event] window resized to " << width << " x " << height;
  return ss.str();
}

} // namespace engine
