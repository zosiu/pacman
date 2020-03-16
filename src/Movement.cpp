#include "pch.hpp"

#include "Movement.hpp"

namespace pacman {

Movement::Movement(Coord starting_position, Direction starting_direction, float ms_per_tile, const Level *level)
    : starting_position(std::move(starting_position)), starting_direction(starting_direction),
      position(starting_position), direction(starting_direction), ms_per_tile(ms_per_tile), level(level) {}

void Movement::set_can_move_into_predicate(const CanMoveIntoPredicate &predicate) { can_move_into = predicate; }

void Movement::set_next_direction_callback(const NextDirectionCallback &callback) { next_direction = callback; }

void Movement::set_after_move_callback(const AfterMoveCallback &callback) { after_move = callback; }

const Coord &Movement::get_position() const { return position; }

TileCoord Movement::get_tile() const { return {floorf(position.x), floorf(position.y)}; }

Direction Movement::get_direction() const { return direction; }

std::unordered_map<Direction, TileCoord> Movement::possible_turns() const {
  std::unordered_map<Direction, TileCoord> directions;
  if (can_turn_up())
    directions[Direction::Up] = get_tile() + direction_to_vec(Direction::Up);
  if (can_turn_left())
    directions[Direction::Left] = get_tile() + direction_to_vec(Direction::Left);
  if (can_turn_down())
    directions[Direction::Down] = get_tile() + direction_to_vec(Direction::Down);
  if (can_turn_right())
    directions[Direction::Right] = get_tile() + direction_to_vec(Direction::Right);

  return directions;
}

void Movement::reset() {
  position = starting_position;
  direction = starting_direction;
}

void Movement::move() {
  planned_direction = next_direction({direction, possible_turns()});

  if (planned_direction_is_feasible()) {
    direction = planned_direction;
    planned_direction = Direction::None;
  }

  auto tile_before = get_tile();

  if (is_blocked()) {
    planned_direction = Direction::None;
  } else {
    position += (glm::vec<2, float>)direction_to_vec(direction) / ms_per_tile;
  }

  after_move({tile_before, get_tile()});
}

TileCoord Movement::next_tile() const { return get_tile() + direction_to_vec(direction); }

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

bool Movement::can_turn_up() const {
  return is_on_tile_x_edge() && can_move_into(level->at(get_tile() + direction_to_vec(Direction::Up)));
}

bool Movement::can_turn_down() const {
  return is_on_tile_x_edge() && can_move_into(level->at(get_tile() + direction_to_vec(Direction::Down)));
}

bool Movement::can_turn_left() const {
  return is_on_tile_y_edge() && can_move_into(level->at(get_tile() + direction_to_vec(Direction::Left)));
}

bool Movement::can_turn_right() const {
  return is_on_tile_y_edge() && can_move_into(level->at(get_tile() + direction_to_vec(Direction::Right)));
}

bool Movement::is_blocked() const { return is_on_tile_edge() && !can_move_into(level->at(next_tile())); }

bool Movement::planned_direction_is_feasible() const {
  return (planned_direction == Direction::Right && can_turn_right()) ||
         (planned_direction == Direction::Left && can_turn_left()) ||
         (planned_direction == Direction::Down && can_turn_down()) ||
         (planned_direction == Direction::Up && can_turn_up());
}

} // namespace pacman
