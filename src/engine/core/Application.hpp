#pragma once

#ifndef BDAD030F_9134_3B0B_5632_EF8DD6E3142E
#define BDAD030F_9134_3B0B_5632_EF8DD6E3142E

#include "../../Ghost.hpp"
#include "../../Level.hpp"
#include "../../Player.hpp"
#include "../../pch.hpp"
#include "../events/ApplicationEvents.hpp"
#include "../events/Event.hpp"
#include "../utils/OrthographicCamera.hpp"
#include "Window.hpp"
#include <glm/glm.hpp>

namespace engine {

class Application {
public:
  Application(uint16_t width = 1024, uint16_t height = 768);
  ~Application();

  void run();
  void on_event(const Event &event);

private:
  void on_window_close(const WindowClosedEvent &event);
  void on_window_resize(const WindowResizedEvent &event);

private:
  bool running = true;
  std::unique_ptr<OrthographicCamera> camera;
  std::unique_ptr<Window> window;
  pacman::Level level_map;

  std::unique_ptr<pacman::Player> player;
  std::vector<pacman::Ghost> ghosts;
};

} // namespace engine

#endif /* BDAD030F_9134_3B0B_5632_EF8DD6E3142E */
