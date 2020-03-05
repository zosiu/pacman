#include "Level.hpp"
#include "./engine/OpenGL/renderer/BatchRenderer2D.hpp"

namespace pacman {

size_t Level::number_of_rows() const { return layout.size(); }
size_t Level::number_of_columns() const { return layout[0].size(); }

Tile Level::at(int x, int y) const {
  if (x < 0 || y < 0 || x >= (int)number_of_columns() || y >= (int)number_of_rows())
    return Tile::Void;

  return layout.at(y).at(x);
}

void Level::render() {
  const glm::vec2 tile_size{1, 1};

  for (size_t y = 0; y < number_of_rows(); ++y) {
    for (size_t x = 0; x < number_of_columns(); ++x) {
      glm::vec2 pos = {x, y};

      switch (layout[y][x]) {
      case Tile::Wall:
        engine::BatchRenderer2D::draw_quad(pos, tile_size, {0.0f, 0.0f, 0.5f, 1.0f});
        break;
      case Tile::Floor:
        engine::BatchRenderer2D::draw_quad(pos, tile_size, {0.0f, 0.0f, 0.0f, 1.0f});
        break;
      case Tile::Void:
        break;
      }
    }
  }
}

} // namespace pacman
