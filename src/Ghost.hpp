#pragma once

#ifndef G280C0FF_2134_3B70_DE3E_712C7D9F7AC9
#define G280C0FF_2134_3B70_DE3E_712C7D9F7AC9

#include "Movement.hpp"
#include "glm/glm.hpp"

namespace pacman {

class Ghost {
public:
  Ghost(glm::vec4 color, glm::vec2 starting_position, Direction starting_direction, float speed, const Level *level);

  const glm::vec2 &get_position() const;

  void update();
  void render() const;

private:
  void render_body() const;
  void render_pupils() const;
  void render_eye_whites() const;

private:
  glm::vec4 color;
  Movement movement;
};

} // namespace pacman

#endif /* G280C0FF_2134_3B70_DE3E_712C7D9F7AC9 */
