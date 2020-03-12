#pragma once
#ifndef DB12CA75_E9FF_4514_A818_F4962D72FB13
#define DB12CA75_E9FF_4514_A818_F4962D72FB13

#include "Agent.hpp"
#include "Direction.hpp"
#include "Level.hpp"
#include "Movement.hpp"

namespace pacman {

class Player : public Agent {
public:
  Player(Coord starting_position, Direction starting_direction, float speed, Level *level);

  void request_direction(Direction direction);

  void update() override;
  void render() const override;

private:
  void render_body() const;
  void render_mouth() const;

private:
  Level *level_map;
};

} // namespace pacman

#endif /* DB12CA75_E9FF_4514_A818_F4962D72FB13 */
