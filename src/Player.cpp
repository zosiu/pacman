#include "Player.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"
#include "pch.hpp"

namespace pacman {

Player::Player(glm::vec2 starting_position, Direction starting_direction, float speed, const Level *level)
    : movement(starting_position, starting_direction, speed, level) {}

void Player::update() { movement.move(); }

void Player::render() {
  render_body();
  render_mouth();
}

void Player::render_body() {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  glm::vec4 bg_color = {0.0f, 0.0f, 0.0f, 1.0f};

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1, 1}, color);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {3 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 6 / 9.0, pos_y}, {3 / 9.0, 1 / 9.0}, bg_color);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 8 / 9.0, pos_y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, bg_color);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 6 / 9.0}, {1 / 9.0, 2 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 8 / 9.0, pos_y + 6 / 9.0}, {1 / 9.0, 2 / 9.0}, bg_color);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 6 / 9.0, pos_y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, bg_color);
}

void Player::render_mouth() {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  const glm::vec4 bg_color = {0.0f, 0.0f, 0.0f, 1.0f};

  glm::vec2 mouth_starting_pos;
  glm::vec2 lip1_starting_pos;
  glm::vec2 lip2_starting_pos;
  glm::vec2 mouth_size;
  const glm::vec2 lip_size = {1 / 9.0, 1 / 9.0};

  switch (movement.get_direction()) {
  case Direction::None:
    return;
  case Direction::Up:
    mouth_size = {3 / 9.0, 5 / 9.0};
    mouth_starting_pos = {pos_x + 3 / 9.0, pos_y};
    lip1_starting_pos = {pos_x + 2 / 9.0, pos_y};
    lip2_starting_pos = {pos_x + 6 / 9.0, pos_y};
    break;
  case Direction::Down:
    mouth_size = {3 / 9.0, 5 / 9.0};
    mouth_starting_pos = {pos_x + 3 / 9.0, pos_y + 4 / 9.0};
    lip1_starting_pos = {pos_x + 2 / 9.0, pos_y + 8 / 9.0};
    lip2_starting_pos = {pos_x + 6 / 9.0, pos_y + 8 / 9.0};
    break;
  case Direction::Left:
    mouth_size = {5 / 9.0, 3 / 9.0};
    mouth_starting_pos = {pos_x, pos_y + 3 / 9.0};
    lip1_starting_pos = {pos_x, pos_y + 2 / 9.0};
    lip2_starting_pos = {pos_x, pos_y + 6 / 9.0};
    break;
  case Direction::Right:
    mouth_size = {5 / 9.0, 3 / 9.0};
    mouth_starting_pos = {pos_x + 4 / 9.0, pos_y + 3 / 9.0};
    lip1_starting_pos = {pos_x + 8 / 9.0, pos_y + 2 / 9.0};
    lip2_starting_pos = {pos_x + 8 / 9.0, pos_y + 6 / 9.0};
    break;
  }

  engine::BatchRenderer2D::draw_quad(mouth_starting_pos, mouth_size, bg_color);
  engine::BatchRenderer2D::draw_quad(lip1_starting_pos, lip_size, color);
  engine::BatchRenderer2D::draw_quad(lip2_starting_pos, lip_size, color);
}

void Player::request_direction(Direction direction) { movement.request_direction(direction); }

const glm::vec2 &Player::get_position() const { return movement.get_position(); }

} // namespace pacman
