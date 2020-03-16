#pragma once

#ifndef BDAD030F_9134_3B0B_5632_EF8DD6E3142E
#define BDAD030F_9134_3B0B_5632_EF8DD6E3142E

#include "../events/ApplicationEvents.hpp"
#include "../events/Event.hpp"
#include "../utils/OrthographicCamera.hpp"
#include "Layer.hpp"
#include "Window.hpp"

namespace engine {

// Application class for
// * window handling
// * camera handling
// * handling applciation logic through layers
// * propagating events to layers
class Application {
public:
  Application(const std::string &window_name, uint16_t width = 1024, uint16_t height = 768);

  void run();
  void on_event(const Event &event);
  void attach_layer(Layer *layer);

private:
  void on_window_close(const WindowClosedEvent &event);
  void on_window_resize(const WindowResizedEvent &event);

private:
  bool running = true;
  float last_frame_time = 0.0f;

  std::unique_ptr<Window> window;
  std::unique_ptr<OrthographicCamera> camera;
  std::vector<Layer *> layers;
};

} // namespace engine

#endif /* BDAD030F_9134_3B0B_5632_EF8DD6E3142E */
