#pragma once

#ifndef D9D10969_0134_3B70_CAA7_B2AA22E94C72
#define D9D10969_0134_3B70_CAA7_B2AA22E94C72

#include "Direction.hpp"
#include "Level.hpp"

namespace pacman {

class Movement {
public:
  Movement(glm::vec2 starting_position, Direction starting_direction, float ms_per_tile, const Level *level);

  const glm::vec2 &get_position() const;
  glm::vec<2, int> get_tile() const;
  Direction get_direction() const;
  Direction get_requested_direction() const;

  void move();
  void request_direction(Direction direction);

private:
  glm::vec2 position;
  Direction direction;
  float speed;
  Direction requested_direction = Direction::None;

  const Level *level;
};

} // namespace pacman

#endif /* D9D10969_0134_3B70_CAA7_B2AA22E94C72 */
