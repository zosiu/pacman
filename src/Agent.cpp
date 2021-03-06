#include "pch.hpp"

#include "Level.hpp"

#include "Agent.hpp"

namespace pacman {

Agent::Agent(Coord starting_position, Direction starting_direction, float speed, const Level *level)
    : movement(starting_position, starting_direction, speed, level) {

  // some abitrary defaults, it's up to the descendant to specify these for itself
  movement.set_can_move_into_predicate([](Tile) { return false; });
  movement.set_next_direction_callback([](const DirectionInfo &info) { return info.current_direction; });
  movement.set_after_move_callback([](const MoveInfo & /* info */) {});
}

void Agent::reset() { movement.reset(); }

void Agent::update() { movement.move(); }

bool Agent::collides_with(const Agent &other_agent) const {
  return glm::distance(movement.get_position(), other_agent.movement.get_position()) < 0.95f;
}

TileCoord Agent::get_tile() const { return movement.get_tile(); }

Direction Agent::get_direction() const { return movement.get_direction(); }

} // namespace pacman
