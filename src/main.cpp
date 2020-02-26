#include "engine/core/Application.hpp"
#include "pch.hpp"

int main() {
  engine::Logger::init("pacman.log");
  auto app = std::make_unique<engine::Application>();
  app->run();

  return 0;
}
