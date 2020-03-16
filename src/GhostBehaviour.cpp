#include "pch.hpp"

#include "GhostBehaviour.hpp"

namespace pacman {

GhostBehaviour::GhostBehaviour(GhostBehaviourType type) : type(type) {}

Direction GhostBehaviour::next_direction(const DirectionInfo &info) {
  switch (type) {
  case GhostBehaviourType::Random:
    return random_direction(info);
  }
}

Direction GhostBehaviour::random_direction(const DirectionInfo &info) {
  Direction opposite = opposite_of(info.current_direction);
  std::vector<Direction> turns_without_going_back;
  std::copy_if(info.possible_turns.begin(), info.possible_turns.end(), std::back_inserter(turns_without_going_back),
               [&opposite](auto dir) { return dir != opposite; });

  return turns_without_going_back.empty() ? info.current_direction
                                          : turns_without_going_back[rand() % turns_without_going_back.size()];
}

} // namespace pacman
