#include "Text.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"

namespace pacman {

void Text::render_you_win(const glm::vec2 &pos) {
  const glm::vec4 you_color = {1.0f, 1.0f, 1.0f, 1.0f};
  const glm::vec4 win_color = {0.0f, 1.0f, 0.0f, 1.0f};

  render_y({pos.x, pos.y}, you_color);
  render_o({pos.x + 1, pos.y}, you_color);
  render_u({pos.x + 2, pos.y}, you_color);

  render_w({pos.x, pos.y + 1}, win_color);
  render_i({pos.x + 1, pos.y + 1}, win_color);
  render_n({pos.x + 2, pos.y + 1}, win_color);
}

void Text::render_you_lose(const glm::vec2 &pos) {
  const glm::vec4 you_color = {1.0f, 1.0f, 1.0f, 1.0f};
  const glm::vec4 lose_color = {1.0f, 0.0f, 0.0f, 1.0f};

  render_y({pos.x, pos.y}, you_color);
  render_o({pos.x + 1, pos.y}, you_color);
  render_u({pos.x + 2, pos.y}, you_color);

  render_l({pos.x - 0.5, pos.y + 1}, lose_color);
  render_o({pos.x + 0.5, pos.y + 1}, lose_color);
  render_s({pos.x + 1.5, pos.y + 1}, lose_color);
  render_e({pos.x + 2.5, pos.y + 1}, lose_color);
}

void Text::render_y(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 3 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 3 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 4 / 9.0}, {1 / 9.0, 5 / 9.0}, color);
}

void Text::render_o(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y}, {3 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 5 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 5 / 9.0}, color);
}

void Text::render_u(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, color);
}

void Text::render_w(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 6 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
}

void Text::render_i(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y}, {1 / 9.0, 1}, color);
}

void Text::render_n(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 4 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 6 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
}

void Text::render_l(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 8 / 9.0}, {6 / 9.0, 1 / 9.0}, color);
}

void Text::render_s(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 4 / 9.0}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 8 / 9.0}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 5 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
}

void Text::render_e(const glm::vec2 &pos, const glm::vec4 &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 4 / 9.0}, {6 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 8 / 9.0}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 5 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
}

} // namespace pacman
