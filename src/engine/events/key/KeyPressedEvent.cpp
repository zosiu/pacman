#include "../../../pch.hpp"

#include "KeyPressedEvent.hpp"

namespace engine {

KeyPressedEvent::KeyPressedEvent(KeyCode key_code, bool repeated_or_not)
    : key_code(key_code), repeated(repeated_or_not) {}

EventType KeyPressedEvent::get_static_type() { return EventType::KeyPressed; }

EventType KeyPressedEvent::get_event_type() const { return get_static_type(); }

KeyCode KeyPressedEvent::get_key_code() const { return key_code; }
bool KeyPressedEvent::is_repeated() const { return repeated; }

std::string KeyPressedEvent::get_name() const {
  std::stringstream ss;
  ss << "[key event] { " << key_code << " } key pressed";
  if (repeated) {
    ss << " (repeatedly)";
  }

  return ss.str();
}

} // namespace engine
