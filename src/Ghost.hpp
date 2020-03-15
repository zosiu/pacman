#pragma once

#ifndef G280C0FF_2134_3B70_DE3E_712C7D9F7AC9
#define G280C0FF_2134_3B70_DE3E_712C7D9F7AC9

#include "Agent.hpp"
#include "Direction.hpp"
#include "Movement.hpp"

namespace pacman {

class Ghost : public Agent {

public:
  Ghost(Color color, Coord starting_position, Direction starting_direction, float speed, const Level *level);

  void render() const override;

private:
  bool can_move_into(Tile tile) const;
  Direction next_direction(const DirectionInfo &info) const;
  inline void render_body() const;
  inline void render_pupils() const;
  inline void render_eye_whites() const;

private:
  Color color;
};

} // namespace pacman

#endif /* G280C0FF_2134_3B70_DE3E_712C7D9F7AC9 */
