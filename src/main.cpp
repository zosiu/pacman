#include "pch.hpp"

#include "engine/core/Application.hpp"

#include "GameLayer.hpp"

int main() {
  engine::Logger::init("pacman.log");
  auto app = std::make_unique<engine::Application>("PACman");
  auto game_layer = std::make_unique<pacman::GameLayer>();
  app->attach_layer(game_layer.get());

  app->run();

  return 0;
}
