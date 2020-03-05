#include "Ghost.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"
#include "pch.hpp"

namespace pacman {

Ghost::Ghost(glm::vec4 color, glm::vec2 starting_position, Direction starting_direction, float speed,
             const Level *level)
    : color(std::move(color)), movement(starting_position, starting_direction, speed, level) {}

void Ghost::update() {
  movement.move();

  std::array<Direction, 4> directions = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
  Direction opposite = Direction::None;
  switch (movement.get_direction()) {
  case Direction::Up:
    opposite = Direction::Down;
    break;
  case pacman::Direction::Down:
    opposite = Direction::Up;
    break;
  case pacman::Direction::Left:
    opposite = Direction::Right;
    break;
  case pacman::Direction::Right:
    opposite = Direction::Left;
    break;
  case Direction::None:
    break;
  }

  std::remove(directions.begin(), directions.end(), opposite);

  if (movement.get_requested_direction() == Direction::None) {
    movement.request_direction(directions[rand() % 3]);
  }
}

void Ghost::render() { engine::BatchRenderer2D::draw_quad(movement.get_position(), {1, 1}, color); }

} // namespace pacman
