#pragma once

#ifndef BB63AAA9_A134_3B6F_1606_14707E2957F6
#define BB63AAA9_A134_3B6F_1606_14707E2957F6

namespace pacman {

enum class Tile { Void, Wall, Floor };

struct Vec2KeyFunc {
  size_t operator()(const TileCoord &k) const { return std::hash<int>()(k.x) ^ std::hash<int>()(k.y); }
  bool operator()(const TileCoord &a, const TileCoord &b) const { return a.x == b.x && a.y == b.y; }
};

class Level {
public:
  Level();

  size_t number_of_rows() const;
  size_t number_of_columns() const;

  Tile at(TileCoord coord) const;

  bool no_more_pellets() const;
  void erase_pellet(const TileCoord &tile);

  void render() const;

private:
  std::unordered_set<TileCoord, Vec2KeyFunc, Vec2KeyFunc> pellets;
  std::array<std::array<Tile, 23>, 23> layout = {{
      {
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Wall,
      },
      {
          Tile::Void, Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,
      },
      {
          Tile::Void, Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,
      },
      {
          Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,
      },
      {
          Tile::Void, Tile::Void, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Void, Tile::Void,
      },
      {
          Tile::Void,  Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,
      },
      {
          Tile::Void, Tile::Void, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Void, Tile::Void,
      },
      {
          Tile::Void, Tile::Void,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Void,  Tile::Void,
      },
      {
          Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Floor, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall,  Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Wall,  Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Floor,
          Tile::Wall, Tile::Floor, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Wall,  Tile::Wall,  Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall, Tile::Floor, Tile::Wall,  Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall,  Tile::Wall,  Tile::Wall, Tile::Wall,  Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall,  Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor,
          Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Floor, Tile::Wall,
      },
      {
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
          Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
      },
      //    {
      //        Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void,
      //        Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void,
      //        Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void, Tile::Void,
      //    }
  }};
};

} // namespace pacman

#endif /* BB63AAA9_A134_3B6F_1606_14707E2957F6 */
