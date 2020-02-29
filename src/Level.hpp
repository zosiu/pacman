#pragma once

#ifndef BB63AAA9_A134_3B6F_1606_14707E2957F6
#define BB63AAA9_A134_3B6F_1606_14707E2957F6

#include "pch.hpp"

namespace pacman {

enum class Tile { Void, Wall, Floor, Pen };

class Level {
public:
  size_t number_of_rows() const;
  size_t number_of_columns() const;

  Tile at(int x, int y) const;

  void render();

private:
  std::array<std::array<Tile, 23>, 24> layout = {
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,
      Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Void,
      Tile::Void,  Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,
      Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,  Tile::Void,
      Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Pen,   Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Pen,
      Tile::Pen,   Tile::Pen,   Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,
      Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,
      Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
      Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,
      Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,
      Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,  Tile::Void,

  };
};

} // namespace pacman

#endif /* BB63AAA9_A134_3B6F_1606_14707E2957F6 */
