#pragma once
#ifndef BE2A1078_CDA4_41C5_A771_03439F2A169A
#define BE2A1078_CDA4_41C5_A771_03439F2A169A

#include "../events/Event.hpp"

namespace engine {

class Layer {
public:
  virtual ~Layer() = default;

  virtual void on_attach() = 0;
  virtual void on_update(float time_since_last_update_in_ms) = 0;
  virtual void on_event(const Event &event) = 0;
};

} // namespace engine

#endif /* BE2A1078_CDA4_41C5_A771_03439F2A169A */
