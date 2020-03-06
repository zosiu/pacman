#include "Level.hpp"
#include "./engine/OpenGL/renderer/BatchRenderer2D.hpp"
#include "Constants.hpp"

namespace pacman {

constexpr glm::vec4 COLOR_WALL = {0.0f, 0.0f, 0.4f, 1.0f};
constexpr glm::vec4 COLOR_PELLET = {1.0f, 1.0f, 1.0f, 1.0f};

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

void Level::render() const {
  const glm::vec2 tile_size{1, 1};

  for (size_t y = 0; y < number_of_rows(); ++y) {
    for (size_t x = 0; x < number_of_columns(); ++x) {
      glm::vec2 pos = {x, y};

      switch (layout[y][x]) {
      case Tile::Wall:
        engine::BatchRenderer2D::draw_quad(pos, tile_size, COLOR_WALL);
        break;
      case Tile::Floor:
        engine::BatchRenderer2D::draw_quad(pos, tile_size, COLOR_FLOOR);
        break;
      case Tile::Void:
        break;
      }
    }
  }

  for (const auto &pellet : pellets) {
    engine::BatchRenderer2D::draw_quad({pellet.x + 4 / 9.0, pellet.y + 4 / 9.0}, {1 / 9.0, 1 / 9.0}, COLOR_PELLET);
  }
}

} // namespace pacman
