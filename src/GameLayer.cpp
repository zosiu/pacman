#include "GameLayer.hpp"
#include "engine/OpenGL/renderer/BatchRenderer2D.hpp"
#include <glad/glad.h>
#include "Text.hpp"

namespace pacman {

GameLayer::GameLayer() : Layer() {
  constexpr float player_ms_per_tile = 215.0f;
  constexpr float ghost_ms_per_tile = 190.0f;

  constexpr glm::vec4 red = {1.0f, 0.0f, 0.0f, 1.0f};
  constexpr glm::vec4 pink = {1.0f, 0.5f, 1.0f, 1.0f};
  constexpr glm::vec4 cyan = {0.0f, 1.0f, 1.0f, 1.0f};
  constexpr glm::vec4 orange = {1.0f, 0.5f, 0.25f, 1.0f};

  // TODO: get rid of the magic corner numbers
  player = std::make_unique<Player>(glm::vec2({11, 13}), Direction::Right, 215.0f, &level_map);

  ghosts = {
      Ghost(red, {1, 1}, Direction::Right, player_ms_per_tile, &level_map),
      Ghost(pink, {1, 21}, Direction::Up, ghost_ms_per_tile, &level_map),
      Ghost(cyan, {21, 1}, Direction::Down, ghost_ms_per_tile, &level_map),
      Ghost(orange, {21, 21}, Direction::Left, ghost_ms_per_tile, &level_map),
  };

  engine::BatchRenderer2D::init();
}

GameLayer::~GameLayer() { engine::BatchRenderer2D::destroy(); }

void GameLayer::on_attach() {
  shader = std::make_unique<engine::OpenGLShaderProgram>("shaders/base.vert.glsl", "shaders/base.frag.glsl");
  shader->bind();

  const auto [min_tiles, max_tiles] = std::minmax({level_map.number_of_columns(), level_map.number_of_rows()});
  const float t = 2.0f / (float)max_tiles;
  const float x_correction =
      level_map.number_of_columns() < level_map.number_of_rows() ? (max_tiles - min_tiles) / float(max_tiles) : 0.0f;
  const auto model_transform = glm::mat4({{t, 0.0f, 0.0f, 0.0f},   //
                                          {0.0f, -t, 0.0f, 0.0f},  //
                                          {0.0f, 0.0f, 0.0, 0.0f}, //
                                          {-1.0f + x_correction, 1.0f, 0.0, 1.0}});

  engine::OpenGLShaderProgram::upload_model_transformation_uniform(model_transform);
  engine::BatchRenderer2D::init();
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
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  engine::BatchRenderer2D::begin_batch();

  level_map.render();

  player->render();
  for (auto &ghost : ghosts)
    ghost.render();

  if (game_state == GameState::Lost)
    Text::render_you_lose({10, 11});
  if (game_state == GameState::Won)
    Text::render_you_win({10, 11});

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
