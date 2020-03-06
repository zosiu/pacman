#include "Ghost.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"
#include "pch.hpp"

namespace pacman {

Ghost::Ghost(glm::vec4 color, glm::vec2 starting_position, Direction starting_direction, float speed, Level *level)
    : color(std::move(color)), movement(starting_position, starting_direction, speed, level) {}

const glm::vec2 &Ghost::get_position() const { return movement.get_position(); }

void Ghost::update() {
  movement.move();

  std::array<Direction, 4> directions = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
  Direction opposite = Direction::None;
  switch (movement.get_direction()) {
  case Direction::Up:
    opposite = Direction::Down;
    break;
  case Direction::Down:
    opposite = Direction::Up;
    break;
  case Direction::Left:
    opposite = Direction::Right;
    break;
  case Direction::Right:
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

void Ghost::render() const {
  render_body();
  render_eye_whites();
  render_pupils();
}

void Ghost::render_body() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  const glm::vec4 bg_color = {0.0f, 0.0f, 0.0f, 1.0f};

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1, 1}, color);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1 / 9.0, 2 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 1 / 9.0, pos_y}, {1 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 7 / 9.0, pos_y}, {1 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 8 / 9.0, pos_y}, {1 / 9.0, 2 / 9.0}, bg_color);

  engine::BatchRenderer2D::draw_quad({pos_x + 1 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 3 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 5 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, bg_color);
  engine::BatchRenderer2D::draw_quad({pos_x + 7 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, bg_color);
}

void Ghost::render_pupils() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  glm::vec2 starting_pos;
  switch (movement.get_direction()) {
  case Direction::None:
    return;
  case Direction::Up:
    starting_pos = {pos_x + 2 / 9.0, pos_y + 1 / 9.0};
    break;
  case Direction::Down:
    starting_pos = {pos_x + 2 / 9.0, pos_y + 3 / 9.0};
    break;
  case Direction::Left:
    starting_pos = {pos_x, pos_y + 3 / 9.0};
    break;
  case Direction::Right:
    starting_pos = {pos_x + 4 / 9.0, pos_y + 3 / 9.0};
    break;
  }

  const glm::vec4 dark_blue = {0.0f, 0.0f, 0.2f, 1.0f};
  const glm::vec2 pupil_size = {1 / 9.0, 2 / 9.0};
  engine::BatchRenderer2D::draw_quad({starting_pos.x, starting_pos.y}, pupil_size, dark_blue);
  engine::BatchRenderer2D::draw_quad({starting_pos.x + 4 / 9.0, starting_pos.y}, pupil_size, dark_blue);
}

void Ghost::render_eye_whites() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  glm::vec2 starting_pos;
  switch (movement.get_direction()) {
  case Direction::None:
    return;
  case Direction::Up:
    starting_pos = {pos_x + 1 / 9.0, pos_y + 1 / 9.0};
    break;
  case Direction::Down:
    starting_pos = {pos_x + 1 / 9.0, pos_y + 2 / 9.0};
    break;
  case Direction::Left:
    starting_pos = {pos_x, pos_y + 2 / 9.0};
    break;
  case Direction::Right:
    starting_pos = {pos_x + 2 / 9.0, pos_y + 2 / 9.0};
    break;
  }

  const glm::vec4 white = {1.0f, 1.0f, 1.0f, 1.0f};
  const glm::vec2 eye_white_size = {3 / 9.0, 3 / 9.0};
  engine::BatchRenderer2D::draw_quad({starting_pos.x, starting_pos.y}, eye_white_size, white);
  engine::BatchRenderer2D::draw_quad({starting_pos.x + 4 / 9.0, starting_pos.y}, eye_white_size, white);
}

} // namespace pacman
