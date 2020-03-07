#include "Player.hpp"
#include "engine/OpenGL/BatchRenderer2D.hpp"
#include "pch.hpp"
#include "Constants.hpp"

namespace pacman {

constexpr glm::vec4 COLOR_PLAYER = {1.0f, 1.0f, 0.0f, 1.0f};

Player::Player(glm::vec2 starting_position, Direction starting_direction, float speed, Level *level)
    : level_map(level), movement(starting_position, starting_direction, speed, level) {}

void Player::update() {
  movement.move();
  level_map->erase_pellet(movement.get_tile());
}

void Player::render() const {
  render_body();
  render_mouth();
}

void Player::render_body() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1, 1}, COLOR_PLAYER);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {3 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 6 / 9.0, pos_y}, {3 / 9.0, 1 / 9.0}, COLOR_FLOOR);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 8 / 9.0, pos_y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, COLOR_FLOOR);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 6 / 9.0}, {1 / 9.0, 2 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 8 / 9.0, pos_y + 6 / 9.0}, {1 / 9.0, 2 / 9.0}, COLOR_FLOOR);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 6 / 9.0, pos_y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, COLOR_FLOOR);
}

void Player::render_mouth() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

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

  engine::BatchRenderer2D::draw_quad(mouth_starting_pos, mouth_size, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad(lip1_starting_pos, lip_size, COLOR_PLAYER);
  engine::BatchRenderer2D::draw_quad(lip2_starting_pos, lip_size, COLOR_PLAYER);
}

void Player::request_direction(Direction direction) { movement.request_direction(direction); }

const glm::vec2 &Player::get_position() const { return movement.get_position(); }
glm::vec<2, int> Player::get_tile() const { return movement.get_tile(); }

} // namespace pacman
