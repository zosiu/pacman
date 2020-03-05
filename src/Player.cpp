#include "Player.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"
#include "pch.hpp"

namespace pacman {

Player::Player(glm::vec2 starting_position, Direction starting_direction, float speed, const Level *level)
    : movement(starting_position, starting_direction, speed, level) {}

void Player::update() { movement.move(); }

void Player::render() {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;
  glm::vec4 mouth_color = {0.0f, 0.0f, 0.0f, 1.0f};

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1, 1}, color);
  switch (movement.get_direction()) {
  case Direction::Up:
    engine::BatchRenderer2D::draw_quad({pos_x + 1 / 3.0, pos_y}, {1 / 3.0, 1 / 3.0}, mouth_color);
    break;
  case Direction::Down:
    engine::BatchRenderer2D::draw_quad({pos_x + 1 / 3.0, pos_y + 2 / 3.0}, {1 / 3.0, 1 / 3.0}, mouth_color);
    break;
  case Direction::Left:
    engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 1 / 3.0}, {1 / 3.0, 1 / 3.0}, mouth_color);
    break;
  case Direction::Right:
    engine::BatchRenderer2D::draw_quad({pos_x + 2 / 3.0, pos_y + 1 / 3.0}, {1 / 3.0, 1 / 3.0}, mouth_color);
    break;
  case Direction::None:
    break;
  };
} // namespace pacman

void Player::request_direction(Direction direction) { movement.request_direction(direction); }

} // namespace pacman
