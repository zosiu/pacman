#pragma once

#ifndef CF6D635C_18E4_499A_9093_4B53D791B26B
#define CF6D635C_18E4_499A_9093_4B53D791B26B

#include "Direction.hpp"
#include "Movement.hpp"

namespace pacman {

class Agent {
public:
  Agent(Coord starting_position, Direction starting_direction, float speed, const Level *level);
  virtual ~Agent() = default;

  bool collides_with(const Agent &other_agent) const;

  virtual void update() = 0;
  virtual void render() const = 0;

protected:
  Movement movement;
};

} // namespace pacman

#endif /* CF6D635C_18E4_499A_9093_4B53D791B26B */
