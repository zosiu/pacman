#include "pch.hpp"

#include "glm/gtx/norm.hpp"

#include "GhostBehaviour.hpp"

namespace pacman {

constexpr int RANDOM_VICINITY = 6;

GhostBehaviour::GhostBehaviour(GhostBehaviourType type) : type(type) {}

void GhostBehaviour::set_type(GhostBehaviourType type) { this->type = type; }

Direction GhostBehaviour::next_direction(const DirectionInfo &info, const TileCoord &target) const {
  switch (type) {
  case GhostBehaviourType::Random:
    return closest_to_target(info, target + TileCoord{(rand() % (RANDOM_VICINITY * 2)) - RANDOM_VICINITY,
                                                      (rand() % (RANDOM_VICINITY * 2)) - RANDOM_VICINITY});
  case GhostBehaviourType::Target:
    return closest_to_target(info, target);
  default:
    return info.current_direction;
  }
}

std::vector<std::pair<Direction, TileCoord>> GhostBehaviour::turns_without_going_back(const DirectionInfo &info) const {
  Direction opposite = opposite_of(info.current_direction);
  std::vector<std::pair<Direction, TileCoord>> turns_without_going_back;
  std::copy_if(info.possible_turns.begin(), info.possible_turns.end(), std::back_inserter(turns_without_going_back),
               [&opposite](const auto &p) { return p.first != opposite; });
  return turns_without_going_back;
}

Direction GhostBehaviour::closest_to_target(const DirectionInfo &info, const TileCoord &target) const {
  auto possible_turns = turns_without_going_back(info);
  if (possible_turns.empty())
    return info.current_direction;

  // return the turn that leads closest to the given target
  return std::min_element(
             possible_turns.begin(), possible_turns.end(),
             [&target](const std::pair<Direction, glm::vec2> &p1, const std::pair<Direction, glm::vec2> &p2) {
               return glm::distance2(static_cast<glm::vec2>(target), p1.second) <
                      glm::distance2(static_cast<glm::vec2>(target), p2.second);
             })
      ->first;
}

} // namespace pacman
