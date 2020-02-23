#include "WindowClosedEvent.hpp"

namespace engine {

EventType WindowClosedEvent::get_static_type() { return EventType::WindowClosed; }

EventType WindowClosedEvent::get_event_type() const { return get_static_type(); }

std::string WindowClosedEvent::get_name() const { return "[application event] window closed"; }

} // namespace engine
