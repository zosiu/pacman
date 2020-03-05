#pragma once
#ifndef DB12CA75_E9FF_4514_A818_F4962D72FB13
#define DB12CA75_E9FF_4514_A818_F4962D72FB13

#include "Movement.hpp"
#include "glm/glm.hpp"

namespace pacman {

class Player {
public:
  Player(glm::vec2 starting_position, Direction starting_direction, float speed, const Level *level);

  void request_direction(Direction direction);
  const glm::vec2 &get_position() const;

  void update();
  void render();

private:
  void render_body();
  void render_mouth();

private:
  glm::vec4 color = {1.0f, 1.0f, 0.0f, 1.0f};
  Movement movement;
};

} // namespace pacman

#endif /* DB12CA75_E9FF_4514_A818_F4962D72FB13 */
