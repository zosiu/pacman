#include "pch.hpp"

#include "Direction.hpp"
#include "GhostBehaviour.hpp"
#include "Text.hpp"

#include "engine/OpenGL/BatchRenderer2D.hpp"
#include <glad/glad.h>

#include "glm/gtx/norm.hpp"

#include "GameLayer.hpp"

namespace pacman {

constexpr float PLAYER_MS_PER_TILE = 190.0f;
constexpr float GHOST_MS_PER_TILE = PLAYER_MS_PER_TILE * 1.10f;

constexpr Color COLOR_BACKGROUND = {0.0f, 0.0f, 0.0f, 1.0f};

GameLayer::GameLayer() : Layer() {
  engine::BatchRenderer2D::init();
  shader = std::make_unique<engine::ShaderProgram>("shaders/base.vert.glsl", "shaders/base.frag.glsl");

  player = std::make_unique<Player>(level_map.center_floor(), Direction::Right, PLAYER_MS_PER_TILE, &level_map);

  auto ghost_attrs = ghosts_config();
  for (auto ghost : {"blinky", "inky", "pinky", "clyde"}) {
    auto [color, starting_position, starting_direction, behaviour, target_fun] = ghost_attrs.at(ghost);
    ghosts.insert(
        {ghost, std::make_unique<Ghost>(starting_position, starting_direction, GHOST_MS_PER_TILE, &level_map, color)});
    ghosts.at(ghost)->set_behaviour(behaviour);
    ghosts.at(ghost)->set_target_function(target_fun);
  }
}

GameLayer::~GameLayer() { engine::BatchRenderer2D::destroy(); }

// Hardcoded ghost setup
std::unordered_map<std::string, GameLayer::GhostAttrs> GameLayer::ghosts_config() const {
  return {
      {"blinky",
       {{1.0f, 0.0f, 0.0f, 1.0f},
        level_map.north_east_corner_floor(),
        Direction::Left,
        // targets the random vicinity of the player
        GhostBehaviourType::Random,
        [this]() { return this->player->get_tile(); }}},
      {"pinky",
       {{1.0f, 0.5f, 1.0f, 1.0f},
        level_map.north_west_corner_floor(),
        Direction::Down,
        // targets the tile 4 tiles ahead of the player
        GhostBehaviourType::Target,
        [this]() { return this->player->get_tile() + direction_to_vec(this->player->get_direction()) * 4; }}},
      {"inky",
       {{0.0f, 1.0f, 1.0f, 1.0f},
        level_map.south_east_corner_floor(),
        Direction::Up,
        // "Works together" with blinky, targets his mirror position based on a position near the player
        GhostBehaviourType::Target,
        [this]() {
          auto pivot = this->player->get_tile() + direction_to_vec(this->player->get_direction()) * 3;
          auto blinky = (this->ghosts.at("blinky"))->get_tile();
          return TileCoord{2 * pivot.x - blinky.x, 2 * pivot.y - blinky.y};
        }}},
      {"clyde",
       {{1.0f, 0.5f, 0.25f, 1.0f},
        level_map.south_west_corner_floor(),
        Direction::Right,
        // Targets the player if their distance is at most 8 tiles, or the middle of the level otherwise
        GhostBehaviourType::Target,
        [this]() {
          auto pacman = this->player->get_tile();
          auto clyde = (this->ghosts.at("clyde"))->get_tile();
          return glm::distance2(static_cast<glm::vec2>(clyde), static_cast<glm::vec2>(pacman)) <= 64
                     ? pacman
                     : this->level_map.center_floor();
        }}},
  };
}

void GameLayer::on_attach() {
  shader->bind();

  const auto [min_tiles, max_tiles] = std::minmax({level_map.number_of_columns(), level_map.number_of_rows()});
  const float t = 2.0f / (float)max_tiles;
  const float x_correction =
      level_map.number_of_columns() < level_map.number_of_rows() ? (max_tiles - min_tiles) / float(max_tiles) : 0.0f;
  // transform tile coordinates to OpenGL
  const auto model_transform = glm::mat4({{t, 0.0f, 0.0f, 0.0f},   //
                                          {0.0f, -t, 0.0f, 0.0f},  //
                                          {0.0f, 0.0f, 0.0, 0.0f}, //
                                          {-1.0f + x_correction, 1.0f, 0.0, 1.0}});

  engine::ShaderProgram::upload_model_transformation_uniform(model_transform);
}

void GameLayer::reset() {
  level_map.reset();
  player->reset();
  for (auto &p : ghosts)
    p.second->reset();

  game_state = GameState::Paused;
}

void GameLayer::on_update(float time_since_last_update_in_ms) {
  render();
  update(time_since_last_update_in_ms);
}

void GameLayer::update(float time_since_last_update_in_ms) {
  // end the game if any of the ghosts reached the player
  if (std::any_of(ghosts.begin(), ghosts.end(),
                  [this](const auto &p) { return this->player->collides_with(*p.second); })) {
    game_state = GameState::Lost;
  };

  if (game_state == GameState::InProgress) {
    // update agents every millisecond
    for (size_t i = 0; i < time_since_last_update_in_ms; ++i) {
      player->update();

      for (auto &p : ghosts)
        p.second->update();
    }
  }

  // end the game if there are no more pellets for the player to eat
  if (level_map.no_more_pellets())
    game_state = GameState::Won;
}

void GameLayer::render() const {
  glClearColor(COLOR_BACKGROUND.x, COLOR_BACKGROUND.y, COLOR_BACKGROUND.z, COLOR_BACKGROUND.w);
  glClear(GL_COLOR_BUFFER_BIT);

  engine::BatchRenderer2D::begin_batch();

  level_map.render();

  player->render();

  for (auto &p : ghosts)
    p.second->render();

  if (game_state == GameState::Lost)
    Text::render_you_lose({level_map.center_floor().x - 1, level_map.center_floor().y - 2.5});
  if (game_state == GameState::Won)
    Text::render_you_win({level_map.center_floor().x - 1, level_map.center_floor().y - 2.5});
  if (game_state == GameState::Paused)
    Text::render_press_p({level_map.center_floor().x - 2, level_map.center_floor().y - 2.5});

  engine::BatchRenderer2D::end_batch();
  engine::BatchRenderer2D::flush();
}

void GameLayer::on_key_pressed(const engine::KeyPressedEvent &key_press_event) {
  if (game_state == GameState::InProgress) {
    if (key_press_event.get_key_code() == engine::KeyCode::Left || key_press_event.get_key_code() == engine::Key::A) {
      player->request_direction(Direction::Left);
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Right || key_press_event.get_key_code() == engine::Key::D) {
      player->request_direction(Direction::Right);
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Up || key_press_event.get_key_code() == engine::Key::W) {
      player->request_direction(Direction::Up);
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Down || key_press_event.get_key_code() == engine::Key::S) {
      player->request_direction(Direction::Down);
    }
  }

  if (key_press_event.get_key_code() == engine::KeyCode::P) {
    switch (game_state) {
    case GameState::Lost:
    case GameState::Won:
      reset();
      break;
    case GameState::Paused:
      game_state = GameState::InProgress;
      break;
    case GameState::InProgress:
      game_state = GameState::Paused;
      break;
    }
  }
}

void GameLayer::on_event(const engine::Event &event) {
  engine::Event::dispatch<engine::KeyPressedEvent>(event,
                                                   std::bind(&GameLayer::on_key_pressed, this, std::placeholders::_1));
}

} // namespace pacman
