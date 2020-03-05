#include "Level.hpp"
#include "./engine/OpenGL/renderer/BatchRenderer2D.hpp"

namespace pacman {

Level::Level() {
  for (size_t y = 0; y < number_of_rows(); ++y) {
    for (size_t x = 0; x < number_of_columns(); ++x) {
      if (layout[y][x] == Tile::Floor)
        pellets.emplace(glm::vec<2, int>({x, y}));
    }
  }
}

size_t Level::number_of_rows() const { return layout.size(); }

size_t Level::number_of_columns() const { return layout[0].size(); }

bool Level::no_more_pellets() const { return pellets.empty(); }

void Level::erase_pellet(const glm::vec<2, int> &tile) { pellets.erase(tile); }

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

  for (const auto &pellet : pellets) {
    engine::BatchRenderer2D::draw_quad({pellet.x + 4 / 9.0, pellet.y + 4 / 9.0}, {1 / 9.0, 1 / 9.0},
                                       {1.0f, 1.0f, 1.0f, 1.0f});
  }
}

} // namespace pacman
