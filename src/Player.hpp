#pragma once
#ifndef DB12CA75_E9FF_4514_A818_F4962D72FB13
#define DB12CA75_E9FF_4514_A818_F4962D72FB13

#include "Agent.hpp"
#include "Direction.hpp"
#include "Level.hpp"
#include "Movement.hpp"

namespace pacman {

// Player agent:
// direction can be set from the "outside"
// eats pellets when moving onto a new tile
class Player : public Agent {
public:
  Player(Coord starting_position, Direction starting_direction, float speed, Level *level);

  void request_direction(Direction direction);

  void render() const override;

private:
  bool can_move_into(Tile tile) const;
  Direction next_direction(const DirectionInfo &info) const;
  void after_move(const MoveInfo &info);
  inline void render_body() const;
  inline void render_mouth() const;

private:
  Level *level_map;
  Direction requested_direction = Direction::None;
};

} // namespace pacman

#endif /* DB12CA75_E9FF_4514_A818_F4962D72FB13 */
