#pragma once

#ifndef D8385A61_9469_4EB6_A9AF_160F540A35C5
#define D8385A61_9469_4EB6_A9AF_160F540A35C5

namespace pacman {

enum class Direction { None, Up, Down, Left, Right };

Direction opposite_of(Direction direction);

glm::vec<2, int> direction_to_vec(Direction direction);

} // namespace pacman

#endif /* D8385A61_9469_4EB6_A9AF_160F540A35C5 */
