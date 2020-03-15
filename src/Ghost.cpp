#include "pch.hpp"

#include "engine/OpenGL/BatchRenderer2D.hpp"

#include "Ghost.hpp"

namespace pacman {

constexpr Color COLOR_GHOST_EYE = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr Color COLOR_GHOST_PUPIL = {0.0f, 0.0f, 0.4f, 1.0f};

Ghost::Ghost(Color color, Coord starting_position, Direction starting_direction, float speed, const Level *level)
    : Agent(starting_position, starting_direction, speed, level), color(std::move(color)) {

  movement.set_can_move_into_predicate(std::bind(&Ghost::can_move_into, this, std::placeholders::_1));
  movement.set_next_direction_callback(std::bind(&Ghost::next_direction, this, std::placeholders::_1));
}

bool Ghost::can_move_into(Tile tile) const { return tile == Tile::Floor; }

Direction Ghost::next_direction(const DirectionInfo &info) const {
  Direction opposite = opposite_of(info.current_direction);
  std::vector<Direction> turns_without_going_back;
  std::copy_if(info.possible_turns.begin(), info.possible_turns.end(), std::back_inserter(turns_without_going_back),
               [&opposite](auto dir) { return dir != opposite; });

  return turns_without_going_back.empty() ? info.current_direction
                                          : turns_without_going_back[rand() % turns_without_going_back.size()];
}

void Ghost::render() const {
  render_body();
  render_eye_whites();
  render_pupils();
}

void Ghost::render_body() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  const Color COLOR_FLOOR = {0.0f, 0.0f, 0.0f, 1.0f};

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1, 1}, color);

  engine::BatchRenderer2D::draw_quad({pos_x, pos_y}, {1 / 9.0, 2 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 1 / 9.0, pos_y}, {1 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 7 / 9.0, pos_y}, {1 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 8 / 9.0, pos_y}, {1 / 9.0, 2 / 9.0}, COLOR_FLOOR);

  engine::BatchRenderer2D::draw_quad({pos_x + 1 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 3 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 5 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, COLOR_FLOOR);
  engine::BatchRenderer2D::draw_quad({pos_x + 7 / 9.0, pos_y + 8 / 9.0}, {1 / 9.0, 1 / 9.0}, COLOR_FLOOR);
}

void Ghost::render_pupils() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  Coord starting_pos = {pos_x, pos_y};
  switch (movement.get_direction()) {
  case Direction::None:
    return;
  case Direction::Up:
    starting_pos = {pos_x + 2 / 9.0, pos_y + 1 / 9.0};
    break;
  case Direction::Down:
    starting_pos = {pos_x + 2 / 9.0, pos_y + 4 / 9.0};
    break;
  case Direction::Left:
    starting_pos = {pos_x, pos_y + 3 / 9.0};
    break;
  case Direction::Right:
    starting_pos = {pos_x + 4 / 9.0, pos_y + 3 / 9.0};
    break;
  }

  const Coord pupil_size = {1 / 9.0, 2 / 9.0};
  engine::BatchRenderer2D::draw_quad({starting_pos.x, starting_pos.y}, pupil_size, COLOR_GHOST_PUPIL);
  engine::BatchRenderer2D::draw_quad({starting_pos.x + 4 / 9.0, starting_pos.y}, pupil_size, COLOR_GHOST_PUPIL);
}

void Ghost::render_eye_whites() const {
  auto pos_x = movement.get_position().x;
  auto pos_y = movement.get_position().y;

  Coord starting_pos = {pos_x, pos_y};
  switch (movement.get_direction()) {
  case Direction::None:
    return;
  case Direction::Up:
    starting_pos = {pos_x + 1 / 9.0, pos_y + 1 / 9.0};
    break;
  case Direction::Down:
    starting_pos = {pos_x + 1 / 9.0, pos_y + 3 / 9.0};
    break;
  case Direction::Left:
    starting_pos = {pos_x, pos_y + 2 / 9.0};
    break;
  case Direction::Right:
    starting_pos = {pos_x + 2 / 9.0, pos_y + 2 / 9.0};
    break;
  }

  const Coord eye_white_size = {3 / 9.0, 3 / 9.0};
  engine::BatchRenderer2D::draw_quad({starting_pos.x, starting_pos.y}, eye_white_size, COLOR_GHOST_EYE);
  engine::BatchRenderer2D::draw_quad({starting_pos.x + 4 / 9.0, starting_pos.y}, eye_white_size, COLOR_GHOST_EYE);
}

} // namespace pacman
