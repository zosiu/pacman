#include "pch.hpp"

#include "engine/OpenGL/BatchRenderer2D.hpp"

#include "Text.hpp"

namespace pacman {

constexpr Color COLOR_YOU_TEXT = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr Color COLOR_WIN_TEXT = {0.0f, 1.0f, 0.0f, 1.0f};
constexpr Color COLOR_LOSE_TEXT = {1.0f, 0.0f, 0.0f, 1.0f};
constexpr Color COLOR_PRESS_P = {0.8f, 0.8f, 0.8f, 1.0f};

void Text::render_you_win(const Coord &pos) {
  render_y({pos.x, pos.y}, COLOR_YOU_TEXT);
  render_o({pos.x + 1, pos.y}, COLOR_YOU_TEXT);
  render_u({pos.x + 2, pos.y}, COLOR_YOU_TEXT);

  render_w({pos.x, pos.y + 1}, COLOR_WIN_TEXT);
  render_i({pos.x + 1, pos.y + 1}, COLOR_WIN_TEXT);
  render_n({pos.x + 2, pos.y + 1}, COLOR_WIN_TEXT);
}

void Text::render_you_lose(const Coord &pos) {
  render_y({pos.x, pos.y}, COLOR_YOU_TEXT);
  render_o({pos.x + 1, pos.y}, COLOR_YOU_TEXT);
  render_u({pos.x + 2, pos.y}, COLOR_YOU_TEXT);

  render_l({pos.x - 0.5, pos.y + 1}, COLOR_LOSE_TEXT);
  render_o({pos.x + 0.5, pos.y + 1}, COLOR_LOSE_TEXT);
  render_s({pos.x + 1.5, pos.y + 1}, COLOR_LOSE_TEXT);
  render_e({pos.x + 2.5, pos.y + 1}, COLOR_LOSE_TEXT);
}

void Text::render_press_p(const Coord &pos) {
  render_p({pos.x, pos.y}, COLOR_PRESS_P);
  render_r({pos.x + 1, pos.y}, COLOR_PRESS_P);
  render_e({pos.x + 2, pos.y}, COLOR_PRESS_P);
  render_s({pos.x + 3, pos.y}, COLOR_PRESS_P);
  render_s({pos.x + 4, pos.y}, COLOR_PRESS_P);
  render_p({pos.x + 2, pos.y + 1}, COLOR_PRESS_P);
}

void Text::render_y(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 3 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 3 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 4 / 9.0}, {1 / 9.0, 5 / 9.0}, color);
}

void Text::render_o(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y}, {3 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 5 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 5 / 9.0}, color);
}

void Text::render_u(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 8 / 9.0}, {3 / 9.0, 1 / 9.0}, color);
}

void Text::render_w(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 7 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 6 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
}

void Text::render_i(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y}, {1 / 9.0, 1}, color);
}

void Text::render_n(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 3 / 9.0, pos.y + 2 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 4 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 6 / 9.0}, {1 / 9.0, 2 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
}

void Text::render_l(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 8 / 9.0}, {6 / 9.0, 1 / 9.0}, color);
}

void Text::render_s(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 4 / 9.0}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 8 / 9.0}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 5 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
}

void Text::render_e(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 4 / 9.0}, {6 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 8 / 9.0}, {7 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y + 5 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
}

void Text::render_p(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y}, {5 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 4 / 9.0}, {5 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
}

void Text::render_r(const Coord &pos, const Color &color) {
  engine::BatchRenderer2D::draw_quad({pos.x + 1 / 9.0, pos.y}, {1 / 9.0, 1}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y}, {5 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 2 / 9.0, pos.y + 4 / 9.0}, {5 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 1 / 9.0}, {1 / 9.0, 3 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 4 / 9.0, pos.y + 5 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 5 / 9.0, pos.y + 6 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 6 / 9.0, pos.y + 7 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
  engine::BatchRenderer2D::draw_quad({pos.x + 7 / 9.0, pos.y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, color);
}

} // namespace pacman
