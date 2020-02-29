#include "Application.hpp"
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

  player_pos = {11, 13};
  player_dir = {1, 0};

  double last_time = glfwGetTime();
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
    BatchRenderer2D::draw_quad(player_pos, {1, 1}, {1.0f, 1.0f, 0.0f, 1.0f});
    BatchRenderer2D::end_batch();
    BatchRenderer2D::flush();
    window->on_update();

    constexpr float ms_per_tile = 215;
    for (size_t i = 0; i < delta_ms; ++i) {
      int tile_x = floorf(player_pos.x);
      int tile_y = floorf(player_pos.y);

      bool on_tile_x_edge = (int(player_pos.x * ms_per_tile) % int(ms_per_tile) == 0);
      bool on_tile_y_edge = (int(player_pos.y * ms_per_tile) % int(ms_per_tile) == 0);
      bool on_tile_edge = player_dir.x == 0 ? on_tile_y_edge : on_tile_x_edge;

      bool can_go_up = on_tile_x_edge && (level_map.at(tile_x, tile_y - 1) == pacman::Tile::Floor);
      bool can_go_down = on_tile_x_edge && (level_map.at(tile_x, tile_y + 1) == pacman::Tile::Floor);
      bool can_go_left = on_tile_y_edge && (level_map.at(tile_x - 1, tile_y) == pacman::Tile::Floor);
      bool can_go_right = on_tile_y_edge && (level_map.at(tile_x + 1, tile_y) == pacman::Tile::Floor);

      if ((requested_dir.x == 1 && requested_dir.y == 0 && can_go_right) ||
          (requested_dir.x == -1 && requested_dir.y == 0 && can_go_left) ||
          (requested_dir.x == 0 && requested_dir.y == 1 && can_go_down) ||
          (requested_dir.x == 0 && requested_dir.y == -1 && can_go_up)) {
        player_dir = requested_dir;
        requested_dir = {0, 0};
      }

      int next_tile_x = tile_x + player_dir.x;
      int next_tile_y = tile_y + player_dir.y;
      bool blocked = on_tile_edge && (level_map.at(next_tile_x, next_tile_y) != pacman::Tile::Floor);

      if (!blocked) {
        player_pos.x = player_pos.x + player_dir.x / ms_per_tile;
        player_pos.y = player_pos.y + player_dir.y / ms_per_tile;
      }
    }
  }
} // namespace engine

void Application::on_event(const Event &event) {
  Event::dispatch<KeyPressedEvent>(event, [this](const engine::KeyPressedEvent &key_press_event) {
    if (key_press_event.get_key_code() == engine::KeyCode::Escape) {
      this->running = false;
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Left) {
      this->requested_dir = {-1, 0};
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Right) {
      this->requested_dir = {1, 0};
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Up) {
      this->requested_dir = {0, -1};
    }

    if (key_press_event.get_key_code() == engine::KeyCode::Down) {
      this->requested_dir = {0, 1};
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
