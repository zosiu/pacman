#pragma once

#ifndef G280C0FF_2134_3B70_DE3E_712C7D9F7AC9
#define G280C0FF_2134_3B70_DE3E_712C7D9F7AC9

#include "Direction.hpp"
#include "Movement.hpp"

namespace pacman {

class Ghost {

public:
  Ghost(Color color, Coord starting_position, Direction starting_direction, float speed, const Level *level);

  const Coord &get_position() const;

  void update();
  void render() const;

private:
  void choose_a_random_direction_forward();
  void render_body() const;
  void render_pupils() const;
  void render_eye_whites() const;

private:
  Color color;
  Movement movement;
};

} // namespace pacman

#endif /* G280C0FF_2134_3B70_DE3E_712C7D9F7AC9 */
