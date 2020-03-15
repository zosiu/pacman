#include "pch.hpp"

#include "Direction.hpp"

namespace pacman {

Direction opposite_of(Direction direction) {
  switch (direction) {
  case Direction::None:
    return Direction::None;
  case Direction::Up:
    return Direction::Down;
  case Direction::Down:
    return Direction::Up;
  case Direction::Left:
    return Direction::Right;
  case Direction::Right:
    return Direction::Left;
  }
}

glm::vec<2, int> direction_to_vec(Direction direction) {
  switch (direction) {
  case Direction::None:
    return {0, 0};
  case Direction::Up:
    return {0, -1};
  case Direction::Down:
    return {0, 1};
  case Direction::Left:
    return {-1, 0};
  case Direction::Right:
    return {1, 0};
  }
}

} // namespace pacman
