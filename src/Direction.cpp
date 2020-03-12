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

std::array<Direction, 3> directions_exluding(Direction direction) {
  switch (direction) {
  case Direction::None:
    return {Direction::None, Direction::None, Direction::None};
  case Direction::Up:
    return {Direction::Down, Direction::Left, Direction::Right};
  case Direction::Down:
    return {Direction::Up, Direction::Left, Direction::Right};
  case Direction::Left:
    return {Direction::Right, Direction::Up, Direction::Down};
  case Direction::Right:
    return {Direction::Left, Direction::Up, Direction::Down};
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
