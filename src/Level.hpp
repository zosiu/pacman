#pragma once

#ifndef BB63AAA9_A134_3B6F_1606_14707E2957F6
#define BB63AAA9_A134_3B6F_1606_14707E2957F6

namespace pacman {

enum class Tile { Void, Wall, Floor };

struct TileCoord2KeyFunc {
  size_t operator()(const TileCoord &k) const { return std::hash<int>()(k.x) ^ std::hash<int>()(k.y); }
  bool operator()(const TileCoord &a, const TileCoord &b) const { return a.x == b.x && a.y == b.y; }
};

class Level {
public:
  Level();

  size_t number_of_rows() const;
  size_t number_of_columns() const;

  Tile at(TileCoord coord) const;

  TileCoord north_west_corner_floor() const;
  TileCoord north_east_corner_floor() const;
  TileCoord south_west_corner_floor() const;
  TileCoord south_east_corner_floor() const;
  TileCoord center_floor() const;

  bool no_more_pellets() const;
  void erase_pellet(const TileCoord &tile);

  void reset();
  void render() const;

private:
  inline void populate_pellets();

private:
  std::array<std::array<Tile, 23>, 23> layout;
  std::unordered_set<TileCoord, TileCoord2KeyFunc, TileCoord2KeyFunc> pellets;
};

} // namespace pacman

#endif /* BB63AAA9_A134_3B6F_1606_14707E2957F6 */
