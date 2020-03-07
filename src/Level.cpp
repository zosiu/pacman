#include "pch.hpp"

#include "Constants.hpp"

#include "./engine/OpenGL/BatchRenderer2D.hpp"

#include "Level.hpp"

namespace pacman {

constexpr Color COLOR_WALL = {0.0f, 0.0f, 0.4f, 1.0f};
constexpr Color COLOR_PELLET = {1.0f, 1.0f, 1.0f, 1.0f};

Level::Level() {
  for (size_t y = 0; y < number_of_rows(); ++y) {
    for (size_t x = 0; x < number_of_columns(); ++x) {
      if (layout[y][x] == Tile::Floor)
        pellets.emplace(TileCoord({x, y}));
    }
  }
}

size_t Level::number_of_rows() const { return layout.size(); }

size_t Level::number_of_columns() const { return layout[0].size(); }

bool Level::no_more_pellets() const { return pellets.empty(); }

void Level::erase_pellet(const TileCoord &tile) { pellets.erase(tile); }

Tile Level::at(TileCoord coord) const {
  if (coord.x < 0 || coord.y < 0 || coord.x >= (int)number_of_columns() || coord.y >= (int)number_of_rows())
    return Tile::Void;

  return layout.at(coord.y).at(coord.x);
}

void Level::render() const {
  for (size_t y = 0; y < number_of_rows(); ++y) {
    for (size_t x = 0; x < number_of_columns(); ++x) {
      switch (layout[y][x]) {
      case Tile::Wall:
        engine::BatchRenderer2D::draw_quad({x, y}, {1, 1}, COLOR_WALL);
        break;
      case Tile::Floor:
        engine::BatchRenderer2D::draw_quad({x, y}, {1, 1}, COLOR_FLOOR);
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
