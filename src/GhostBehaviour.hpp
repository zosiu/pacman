#pragma once

#ifndef A1FC0543_F95F_4942_9F2C_C7A4E546E806
#define A1FC0543_F95F_4942_9F2C_C7A4E546E806

#include "Movement.hpp"

namespace pacman {

enum class GhostBehaviourType { Random, Target };

class GhostBehaviour {
public:
  GhostBehaviour(GhostBehaviourType type);

  void set_type(GhostBehaviourType type);
  Direction next_direction(const DirectionInfo &info, const TileCoord &target = {0, 0}) const;

private:
  inline Direction closest_to_target(const DirectionInfo &info, const TileCoord &target) const;
  inline std::vector<std::pair<Direction, TileCoord>> turns_without_going_back(const DirectionInfo &info) const;

private:
  GhostBehaviourType type;
};

} // namespace pacman

#endif /* A1FC0543_F95F_4942_9F2C_C7A4E546E806 */
