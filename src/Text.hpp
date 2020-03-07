#pragma once
#ifndef A1FD79AD_8740_4EB9_8959_317F5CD3D21D
#define A1FD79AD_8740_4EB9_8959_317F5CD3D21D

namespace pacman {

class Text {
public:
  static void render_you_win(const glm::vec2 &position);
  static void render_you_lose(const glm::vec2 &position);

private:
  static void render_y(const glm::vec2 &position, const glm::vec4 &color);
  static void render_o(const glm::vec2 &position, const glm::vec4 &color);
  static void render_u(const glm::vec2 &position, const glm::vec4 &color);
  static void render_w(const glm::vec2 &position, const glm::vec4 &color);
  static void render_i(const glm::vec2 &position, const glm::vec4 &color);
  static void render_n(const glm::vec2 &position, const glm::vec4 &color);
  static void render_l(const glm::vec2 &position, const glm::vec4 &color);
  static void render_s(const glm::vec2 &position, const glm::vec4 &color);
  static void render_e(const glm::vec2 &position, const glm::vec4 &color);
};

} // namespace pacman

#endif /* A1FD79AD_8740_4EB9_8959_317F5CD3D21D */
