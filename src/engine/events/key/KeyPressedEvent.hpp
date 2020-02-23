#pragma once
#ifndef CF1439B9_D134_3B08_F75E_779AB070C997
#define CF1439B9_D134_3B08_F75E_779AB070C997

#include "../../core/KeyCodes.hpp"
#include "../Event.hpp"

namespace engine {

class KeyPressedEvent : public Event {
public:
  KeyPressedEvent(KeyCode key_code, bool repeated_or_not);

  static EventType get_static_type();
  std::string get_name() const override;
  EventType get_event_type() const override;

  KeyCode get_key_code() const;
  bool is_repeated() const;

private:
  KeyCode key_code;
  bool repeated;
};

} // namespace engine

#endif /* CF1439B9_D134_3B08_F75E_779AB070C997 */
