#include "pch.hpp"

#include "Direction.hpp"
#include "Text.hpp"

#include "engine/OpenGL/BatchRenderer2D.hpp"
#include <glad/glad.h>

#include "GameLayer.hpp"

namespace pacman {

constexpr float PLAYER_MS_PER_TILE = 215.0f;
constexpr float GHOST_MS_PER_TILE = 190.0f;

constexpr glm::vec4 COLOR_RED_GHOST = {1.0f, 0.0f, 0.0f, 1.0f};
constexpr glm::vec4 COLOR_PINK_GHOST = {1.0f, 0.5f, 1.0f, 1.0f};
constexpr glm::vec4 COLOR_CYAN_GHOST = {0.0f, 1.0f, 1.0f, 1.0f};
constexpr glm::vec4 COLOR_ORANGE_GHOST = {1.0f, 0.5f, 0.25f, 1.0f};

constexpr glm::vec4 COLOR_BACKGROUND = {0.0f, 0.0f, 0.0f, 1.0f};

GameLayer::GameLayer() : Layer() {
  shader = std::make_unique<engine::ShaderProgram>("shaders/base.vert.glsl", "shaders/base.frag.glsl");
  engine::BatchRenderer2D::init();

  ghosts = {
      Ghost(COLOR_RED_GHOST, {1, 1}, Direction::Right, GHOST_MS_PER_TILE, &level_map),
      Ghost(COLOR_PINK_GHOST, {1, 21}, Direction::Up, GHOST_MS_PER_TILE, &level_map),
      Ghost(COLOR_CYAN_GHOST, {21, 1}, Direction::Down, GHOST_MS_PER_TILE, &level_map),
      Ghost(COLOR_ORANGE_GHOST, {21, 21}, Direction::Left, GHOST_MS_PER_TILE, &level_map),
  };
  player = std::make_unique<Player>(glm::vec2({11, 13}), Direction::Right, PLAYER_MS_PER_TILE, &level_map);
}

GameLayer::~GameLayer() { engine::BatchRenderer2D::destroy(); }

void GameLayer::on_attach() {
  shader->bind();

  const auto [min_tiles, max_tiles] = std::minmax({level_map.number_of_columns(), level_map.number_of_rows()});
  const float t = 2.0f / (float)max_tiles;
  const float x_correction =
      level_map.number_of_columns() < level_map.number_of_rows() ? (max_tiles - min_tiles) / float(max_tiles) : 0.0f;
  const auto model_transform = glm::mat4({{t, 0.0f, 0.0f, 0.0f},   //
                                          {0.0f, -t, 0.0f, 0.0f},  //
                                          {0.0f, 0.0f, 0.0, 0.0f}, //
                                          {-1.0f + x_correction, 1.0f, 0.0, 1.0}});

  engine::ShaderProgram::upload_model_transformation_uniform(model_transform);
}

void GameLayer::on_update(float time_since_last_update_in_ms) {
  render();
  update(time_since_last_update_in_ms);
}

void GameLayer::update(float time_since_last_update_in_ms) {
  if (std::any_of(ghosts.begin(), ghosts.end(), [this](const Ghost &ghost) {
        return glm::distance(ghost.get_position(), this->player->get_position()) < 0.9f;
      })) {
    game_state = GameState::Lost;
  };

  if (game_state == GameState::InProgress) {
    for (size_t i = 0; i < time_since_last_update_in_ms; ++i) {
      player->update();

      for (auto &ghost : ghosts)
        ghost.update();
    }
  }

  if (level_map.no_more_pellets())
    game_state = GameState::Won;
}

void GameLayer::render() const {
  glClearColor(COLOR_BACKGROUND.x, COLOR_BACKGROUND.y, COLOR_BACKGROUND.z, COLOR_BACKGROUND.w);
  glClear(GL_COLOR_BUFFER_BIT);

  engine::BatchRenderer2D::begin_batch();

  level_map.render();

  player->render();
  for (auto &ghost : ghosts)
    ghost.render();

  if (game_state == GameState::Lost)
    Text::render_you_lose({10, 10.5});
  if (game_state == GameState::Won)
    Text::render_you_win({10, 10.5});

  engine::BatchRenderer2D::end_batch();
  engine::BatchRenderer2D::flush();
}

void GameLayer::on_key_pressed(const engine::KeyPressedEvent &key_press_event) {
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

  if (key_press_event.get_key_code() == engine::KeyCode::P) {
    switch (game_state) {
    case GameState::Lost:
      break;
    case GameState::Won:
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
