#include "pch.hpp"

#include "Agent.hpp"

namespace pacman {

Agent::Agent(Coord starting_position, Direction starting_direction, float speed, const Level *level)
    : movement(starting_position, starting_direction, speed, level) {}

void Agent::reset() { movement.reset(); }

bool Agent::collides_with(const Agent &other_agent) const {
  return glm::distance(movement.get_position(), other_agent.movement.get_position()) < 0.9f;
}

} // namespace pacman
