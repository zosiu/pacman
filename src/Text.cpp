#include "Text.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"

namespace pacman {

constexpr glm::vec4 COLOR_YOU_TEXT = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr glm::vec4 COLOR_WIN_TEXT = {0.0f, 1.0f, 0.0f, 1.0f};
constexpr glm::vec4 COLOR_LOSE_TEXT = {1.0f, 0.0f, 0.0f, 1.0f};

void Text::render_you_win(const glm::vec2 &pos) {
  render_y({pos.x, pos.y}, COLOR_YOU_TEXT);
  render_o({pos.x + 1, pos.y}, COLOR_YOU_TEXT);
  render_u({pos.x + 2, pos.y}, COLOR_YOU_TEXT);

  render_w({pos.x, pos.y + 1}, COLOR_WIN_TEXT);
  render_i({pos.x + 1, pos.y + 1}, COLOR_WIN_TEXT);
  render_n({pos.x + 2, pos.y + 1}, COLOR_WIN_TEXT);
}

void Text::render_you_lose(const glm::vec2 &pos) {
  render_y({pos.x, pos.y}, COLOR_YOU_TEXT);
  render_o({pos.x + 1, pos.y}, COLOR_YOU_TEXT);
  render_u({pos.x + 2, pos.y}, COLOR_YOU_TEXT);

  render_l({pos.x - 0.5, pos.y + 1}, COLOR_LOSE_TEXT);
  render_o({pos.x + 0.5, pos.y + 1}, COLOR_LOSE_TEXT);
  render_s({pos.x + 1.5, pos.y + 1}, COLOR_LOSE_TEXT);
  render_e({pos.x + 2.5, pos.y + 1}, COLOR_LOSE_TEXT);
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
