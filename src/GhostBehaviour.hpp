#pragma once

#ifndef A1FC0543_F95F_4942_9F2C_C7A4E546E806
#define A1FC0543_F95F_4942_9F2C_C7A4E546E806

#include "Movement.hpp"

namespace pacman {

enum class GhostBehaviourType { Random };

class GhostBehaviour {
public:
  GhostBehaviour(GhostBehaviourType type);

  Direction next_direction(const DirectionInfo &info);

private:
  inline Direction random_direction(const DirectionInfo &info);

private:
  GhostBehaviourType type;
};

} // namespace pacman

#endif /* A1FC0543_F95F_4942_9F2C_C7A4E546E806 */
