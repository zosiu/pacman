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

  void move();
  void request_direction(Direction direction);

private:
  Coord position;
  Direction direction;
  float ms_per_tile;
  const Level *level;

  Direction requested_direction = Direction::None;
};

} // namespace pacman

#endif /* D9D10969_0134_3B70_CAA7_B2AA22E94C72 */
