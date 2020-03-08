#include "pch.hpp"

#include "Movement.hpp"

namespace pacman {

Movement::Movement(Coord starting_position, Direction starting_direction, float ms_per_tile, const Level *level)
    : position(std::move(starting_position)), direction(starting_direction), ms_per_tile(ms_per_tile), level(level) {}

const Coord &Movement::get_position() const { return position; }

TileCoord Movement::get_tile() const { return {(int)floorf(position.x), (int)floorf(position.y)}; }

Direction Movement::get_direction() const { return direction; }

Direction Movement::get_requested_direction() const { return requested_direction; }

void Movement::move() {
  int tile_x = floorf(position.x);
  int tile_y = floorf(position.y);

  bool on_tile_x_edge = (int(position.x * ms_per_tile) % int(ms_per_tile) == 0);
  bool on_tile_y_edge = (int(position.y * ms_per_tile) % int(ms_per_tile) == 0);

  bool can_go_up = on_tile_x_edge && (level->at({tile_x, tile_y - 1}) == Tile::Floor);
  bool can_go_down = on_tile_x_edge && (level->at({tile_x, tile_y + 1}) == Tile::Floor);
  bool can_go_left = on_tile_y_edge && (level->at({tile_x - 1, tile_y}) == Tile::Floor);
  bool can_go_right = on_tile_y_edge && (level->at({tile_x + 1, tile_y}) == Tile::Floor);

  if ((requested_direction == Direction::Right && can_go_right) ||
      (requested_direction == Direction::Left && can_go_left) ||
      (requested_direction == Direction::Down && can_go_down) || //
      (requested_direction == Direction::Up && can_go_up)) {
    direction = requested_direction;
    requested_direction = Direction::None;
  }

  glm::vec<2, int> dir = {0, 0};
  switch (direction) {
  case Direction::None:
    dir = {0, 0};
    break;
  case Direction::Up:
    dir = {0, -1};
    break;
  case Direction::Down:
    dir = {0, 1};
    break;
  case Direction::Left:
    dir = {-1, 0};
    break;
  case Direction::Right:
    dir = {1, 0};
    break;
  }

  int next_tile_x = tile_x + dir.x;
  int next_tile_y = tile_y + dir.y;

  bool on_tile_edge =
      ((direction == Direction::Up) || (direction == Direction::Down)) ? on_tile_y_edge : on_tile_x_edge;
  bool blocked = on_tile_edge && (level->at({next_tile_x, next_tile_y}) != Tile::Floor);

  if (blocked) {
    requested_direction = Direction::None;
  } else {
    position.x = position.x + dir.x / ms_per_tile;
    position.y = position.y + dir.y / ms_per_tile;
  }
}

void Movement::request_direction(Direction direction) { requested_direction = direction; }

} // namespace pacman
