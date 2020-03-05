#include "Application.hpp"
#include "../../Text.hpp"
#include "../../pch.hpp"
#include "../OpenGL/OpenGLShaderProgram.hpp"
#include "../OpenGL/renderer/BatchRenderer2D.hpp"
#include "../events/KeyEvents.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

namespace engine {

Application::Application(uint16_t width, uint16_t height) {
  window = std::make_unique<Window>(WindowProps("PACman", width, height));
  window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
  float aspect_ratio = (float)width / (float)height;
  camera = std::make_unique<OrthographicCamera>(-aspect_ratio, aspect_ratio, -1.0, 1.0);
  BatchRenderer2D::init();

  constexpr float player_ms_per_tile = 215.0f;
  constexpr float ghost_ms_per_tile = 190.0f;

  constexpr glm::vec4 red = {1.0f, 0.0f, 0.0f, 1.0f};
  constexpr glm::vec4 pink = {1.0f, 0.5f, 1.0f, 1.0f};
  constexpr glm::vec4 cyan = {0.0f, 1.0f, 1.0f, 1.0f};
  constexpr glm::vec4 orange = {1.0f, 0.5f, 0.25f, 1.0f};

  // TODO: get rid of the magic corner numbers
  player = std::make_unique<pacman::Player>(glm::vec2({11, 13}), pacman::Direction::Right, 215.0f, &level_map);

  ghosts = {
      pacman::Ghost(red, {1, 1}, pacman::Direction::Right, player_ms_per_tile, &level_map),
      pacman::Ghost(pink, {1, 21}, pacman::Direction::Left, ghost_ms_per_tile, &level_map),
      pacman::Ghost(cyan, {21, 1}, pacman::Direction::Right, ghost_ms_per_tile, &level_map),
      pacman::Ghost(orange, {21, 21}, pacman::Direction::Left, ghost_ms_per_tile, &level_map),
  };
}

Application::~Application() { BatchRenderer2D::destroy(); }

void Application::run() {
  engine::OpenGLShaderProgram program("shaders/base.vert.glsl", "shaders/base.frag.glsl");
  program.bind();

  const auto [min_tiles, max_tiles] = std::minmax(level_map.number_of_columns(), level_map.number_of_rows());
  const float t = 2.0f / (float)max_tiles;
  const float x_correction =
      level_map.number_of_columns() < level_map.number_of_rows() ? (max_tiles - min_tiles) / float(max_tiles) : 0.0f;
  const auto model_transform = glm::mat4({{t, 0.0f, 0.0f, 0.0f},   //
                                          {0.0f, -t, 0.0f, 0.0f},  //
                                          {0.0f, 0.0f, 0.0, 0.0f}, //
                                          {-1.0f + x_correction, 1.0f, 0.0, 1.0}});

  OpenGLShaderProgram::upload_model_transformation_uniform(model_transform);
  OpenGLShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());

  double last_time = glfwGetTime();
  srand(last_time);
  double now_time = 0;
  double delta_ms = 0;

  while (running) {
    now_time = glfwGetTime();
    delta_ms = (now_time - last_time) * 1000;
    last_time = now_time;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    BatchRenderer2D::begin_batch();

    level_map.render();

    player->render();
    for (auto &ghost : ghosts)
      ghost.render();

    if (game_state == GameState::Lost)
      pacman::Text::render_you_lose({10, 11});
    if (game_state == GameState::Won)
      pacman::Text::render_you_win({10, 11});

    BatchRenderer2D::end_batch();
    BatchRenderer2D::flush();

    window->on_update();

    if (std::any_of(ghosts.begin(), ghosts.end(), [this](const pacman::Ghost &ghost) {
          return glm::distance(ghost.get_position(), this->player->get_position()) < 0.9f;
        })) {
      game_state = GameState::Lost;
    };

    if (game_state == GameState::InProgress) {
      for (size_t i = 0; i < delta_ms; ++i) {
        player->update();

        for (auto &ghost : ghosts)
          ghost.update();
      }
    }

    if (level_map.no_more_pellets())
      game_state = GameState::Won;
  }
}

void Application::on_event(const Event &event) {
  Event::dispatch<KeyPressedEvent>(event, [this](const engine::KeyPressedEvent &key_press_event) {
    if (key_press_event.get_key_code() == engine::KeyCode::Escape) {
      this->running = false;
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Left) {
      this->player->request_direction(pacman::Direction::Left);
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Right) {
      this->player->request_direction(pacman::Direction::Right);
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Up) {
      this->player->request_direction(pacman::Direction::Up);
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Down) {
      this->player->request_direction(pacman::Direction::Down);
    }
  });

  Event::dispatch<WindowClosedEvent>(event, std::bind(&Application::on_window_close, this, std::placeholders::_1));
  Event::dispatch<WindowResizedEvent>(event, std::bind(&Application::on_window_resize, this, std::placeholders::_1));
}

void Application::on_window_close(const WindowClosedEvent & /* event */) { running = false; }

void Application::on_window_resize(const WindowResizedEvent &event) {
  uint16_t width = event.get_width();
  uint16_t height = event.get_height();

  float aspect_ratio = (float)width / (float)height;
  camera->set_projection(-aspect_ratio, aspect_ratio, -1.0f, 1.0f);
  OpenGLShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());

  // TODO: this should be somewhere else
  glViewport(0, 0, width, height);
}

} // namespace engine
