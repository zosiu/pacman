#pragma once
#ifndef DB12CA75_E9FF_4514_A818_F4962D72FB13
#define DB12CA75_E9FF_4514_A818_F4962D72FB13

#include "Direction.hpp"
#include "Level.hpp"
#include "Movement.hpp"

namespace pacman {

class Player {
public:
  Player(Coord starting_position, Direction starting_direction, float speed, Level *level);

  void request_direction(Direction direction);
  const Coord &get_position() const;

  void update();
  void render() const;

private:
  void render_body() const;
  void render_mouth() const;

private:
  Color color = {1.0f, 1.0f, 0.0f, 1.0f};
  Level *level_map;
  Movement movement;
};

} // namespace pacman

#endif /* DB12CA75_E9FF_4514_A818_F4962D72FB13 */
