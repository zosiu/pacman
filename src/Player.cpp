#include "pch.hpp"

#include "Constants.hpp"

#include "engine/OpenGL/BatchRenderer2D.hpp"

#include "Player.hpp"

namespace pacman {

constexpr Color COLOR_PLAYER = {1.0f, 1.0f, 0.0f, 1.0f};

Player::Player(Coord starting_position, Direction starting_direction, float speed, Level *level)
    : Agent(starting_position, starting_direction, speed, level), level_map(level) {
  level_map->erase_pellet(movement.get_tile());
  movement.set_can_move_into_predicate(std::bind(&Player::can_move_into, this, std::placeholders::_1));
  movement.set_next_direction_callback(std::bind(&Player::next_direction, this, std::placeholders::_1));
  movement.set_after_move_callback(std::bind(&Player::after_move, this, std::placeholders::_1));
}

bool Player::can_move_into(Tile tile) const { return tile == Tile::Floor; }

Direction Player::next_direction(const DirectionInfo & /* info */) const { return requested_direction; }

void Player::after_move(const MoveInfo &info) {
  if (info.prev_tile != info.current_tile)
    level_map->erase_pellet(info.current_tile);
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

  Coord mouth_starting_pos;
  Coord lip1_starting_pos;
  Coord lip2_starting_pos;
  Coord mouth_size;
  const Coord lip_size = {1 / 9.0, 1 / 9.0};

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

void Player::request_direction(Direction direction) { requested_direction = direction; }

} // namespace pacman
