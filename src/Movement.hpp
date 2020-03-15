#pragma once

#ifndef D9D10969_0134_3B70_CAA7_B2AA22E94C72
#define D9D10969_0134_3B70_CAA7_B2AA22E94C72

#include "Direction.hpp"
#include "Level.hpp"

namespace pacman {

class Movement {
public:
  Movement(Coord starting_position, Direction starting_direction, float ms_per_tile, const Level *level);

  const Coord &get_position() const;
  TileCoord get_tile() const;
  Direction get_direction() const;
  Direction get_requested_direction() const;

  void reset();
  void move();
  void request_direction(Direction direction);

private:
  inline TileCoord current_tile() const;
  inline TileCoord next_tile() const;
  inline bool can_take_requested_direction() const;
  inline bool is_on_tile_x_edge() const;
  inline bool is_on_tile_y_edge() const;
  inline bool is_on_tile_edge() const;
  inline bool can_go_up() const;
  inline bool can_go_down() const;
  inline bool can_go_left() const;
  inline bool can_go_right() const;
  inline bool is_blocked() const;

private:
  Coord starting_position;
  Direction starting_direction;
  Coord position;
  Direction direction;
  float ms_per_tile;
  const Level *level;

  Direction requested_direction = Direction::None;
};

} // namespace pacman

#endif /* D9D10969_0134_3B70_CAA7_B2AA22E94C72 */
