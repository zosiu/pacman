#include "pch.hpp"

#include "Movement.hpp"

namespace pacman {

Movement::Movement(Coord starting_position, Direction starting_direction, float ms_per_tile, const Level *level)
    : starting_position(std::move(starting_position)), starting_direction(starting_direction),
      position(starting_position), direction(starting_direction), ms_per_tile(ms_per_tile), level(level) {}

void Movement::set_can_move_into_predicate(const CanMoveIntoPredicate &predicate) { can_move_into = predicate; }

const Coord &Movement::get_position() const { return position; }

TileCoord Movement::get_tile() const { return {floorf(position.x), floorf(position.y)}; }

Direction Movement::get_direction() const { return direction; }

Direction Movement::get_requested_direction() const { return requested_direction; }

void Movement::request_direction(Direction direction) { requested_direction = direction; }

void Movement::reset() {
  position = starting_position;
  direction = starting_direction;
}

void Movement::move() {
  if (can_take_requested_direction()) {
    direction = requested_direction;
    requested_direction = Direction::None;
  }

  if (is_blocked()) {
    requested_direction = Direction::None;
  } else {
    position += (glm::vec<2, float>)direction_to_vec(direction) / ms_per_tile;
  }
}

TileCoord Movement::current_tile() const { return {floorf(position.x), floorf(position.y)}; }

TileCoord Movement::next_tile() const { return current_tile() + direction_to_vec(direction); }

bool Movement::is_on_tile_x_edge() const { return int(position.x * ms_per_tile) % int(ms_per_tile) == 0; }

bool Movement::is_on_tile_y_edge() const { return int(position.y * ms_per_tile) % int(ms_per_tile) == 0; }

bool Movement::is_on_tile_edge() const {
  switch (direction) {
  case Direction::None:
    return false;
  case Direction::Up:
  case Direction::Down:
    return is_on_tile_y_edge();
  case Direction::Left:
  case Direction::Right:
    return is_on_tile_x_edge();
  }
}

bool Movement::can_go_up() const {
  return is_on_tile_x_edge() && can_move_into(level->at(current_tile() + direction_to_vec(Direction::Up)));
}

bool Movement::can_go_down() const {
  return is_on_tile_x_edge() && can_move_into(level->at(current_tile() + direction_to_vec(Direction::Down)));
}

bool Movement::can_go_left() const {
  return is_on_tile_y_edge() && can_move_into(level->at(current_tile() + direction_to_vec(Direction::Left)));
}

bool Movement::can_go_right() const {
  return is_on_tile_y_edge() && can_move_into(level->at(current_tile() + direction_to_vec(Direction::Right)));
}

bool Movement::is_blocked() const { return is_on_tile_edge() && !can_move_into(level->at(next_tile())); }

bool Movement::can_take_requested_direction() const {
  return (requested_direction == Direction::Right && can_go_right()) ||
         (requested_direction == Direction::Left && can_go_left()) ||
         (requested_direction == Direction::Down && can_go_down()) ||
         (requested_direction == Direction::Up && can_go_up());
}

} // namespace pacman
