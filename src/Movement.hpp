#pragma once

#ifndef D9D10969_0134_3B70_CAA7_B2AA22E94C72
#define D9D10969_0134_3B70_CAA7_B2AA22E94C72

#include "Direction.hpp"
#include "Level.hpp"

namespace pacman {

struct DirectionInfo {
  Direction current_direction;
  std::unordered_map<Direction, TileCoord> possible_turns;
};

struct MoveInfo {
  TileCoord prev_tile;
  TileCoord current_tile;
};

// Represents movement across tiles of a level, characterized by
// * a predicate for deciding if movement is allowed for a given tile
// * a direction (up/down/left/right)
// * the number of milliseconds it takes to go through a tile
class Movement {
public:
  using CanMoveIntoPredicate = std::function<bool(Tile)>;
  using NextDirectionCallback = std::function<Direction(const DirectionInfo &)>;
  using AfterMoveCallback = std::function<void(const MoveInfo &)>;

  Movement(Coord starting_position, Direction starting_direction, float ms_per_tile, const Level *level);

  const Coord &get_position() const;
  TileCoord get_tile() const;
  Direction get_direction() const;

  void reset();
  void move();

  void set_can_move_into_predicate(const CanMoveIntoPredicate &predicate);
  void set_next_direction_callback(const NextDirectionCallback &callback);
  void set_after_move_callback(const AfterMoveCallback &callback);

private:
  inline TileCoord next_tile() const;
  inline bool planned_direction_is_feasible() const;
  inline bool is_on_tile_x_edge() const;
  inline bool is_on_tile_y_edge() const;
  inline bool is_on_tile_edge() const;
  inline bool can_turn_up() const;
  inline bool can_turn_down() const;
  inline bool can_turn_left() const;
  inline bool can_turn_right() const;
  inline bool is_blocked() const;
  inline std::unordered_map<Direction, TileCoord> possible_turns() const;

private:
  Coord starting_position;
  Direction starting_direction;
  Coord position;
  Direction direction;
  Direction planned_direction = Direction::None;
  float ms_per_tile;
  const Level *level;

  CanMoveIntoPredicate can_move_into;
  NextDirectionCallback next_direction;
  AfterMoveCallback after_move;
};

} // namespace pacman

#endif /* D9D10969_0134_3B70_CAA7_B2AA22E94C72 */
