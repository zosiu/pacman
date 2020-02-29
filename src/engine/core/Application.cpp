#include "Application.hpp"
#include "../OpenGL/OpenGLShaderProgram.hpp"
#include "../OpenGL/renderer/BatchRenderer2D.hpp"
#include "../events/KeyEvents.hpp"
#include <glad/glad.h>

namespace engine {

Application::Application(uint16_t width, uint16_t height) {
  window = std::make_unique<Window>(WindowProps("Application", width, height));
  window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
  float aspect_ratio = (float)width / (float)height;
  camera = std::make_unique<OrthographicCamera>(-aspect_ratio, aspect_ratio, -1.0, 1.0);
  BatchRenderer2D::init();
}

Application::~Application() { BatchRenderer2D::destroy(); }

void Application::run() {
  engine::OpenGLShaderProgram program("shaders/base.vert.glsl", "shaders/base.frag.glsl");
  program.bind();

  constexpr int num_of_quads = 20;
  constexpr float quad_size = 1.8f / (float)num_of_quads;

  constexpr char level_layout[21][21] = {
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.'},
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.'},
      {'.', '#', '.', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '.', '#', '.'},
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.'},
      {'.', '#', '.', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#', '#', '.', '#', '.'},
      {'.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.'},
      {'.', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '.'},
      {'.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.'},
      {'#', '#', '#', '#', '#', '.', '#', '.', '#', '#', 'J', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '#', 'J', 'J', 'J', '#', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#'},
      {'.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.'},
      {'.', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '.'},
      {'.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.'},
      {'.', '#', '.', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#', '#', '.', '#', '.'},
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.'},
      {'.', '#', '.', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '.', '#', '.'},
      {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.'},
      {'.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};

  while (running) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    BatchRenderer2D::begin_batch();

    for (auto [y, dy] = std::tuple{-0.9f, num_of_quads}; y < 0.9f; y += quad_size, --dy) {
      for (auto [x, dx] = std::tuple{-0.95f, 0}; x < 0.85f; x += quad_size, ++dx) {
        glm::vec4 color;
        switch (level_layout[dy][dx]) {
        case '#': {
          color = {0.0f, 0.0f, 1.0f, 1.0f};
          break;
        }
        case '.': {
          color = {0.0f, 0.0f, 0.0f, 1.0f};
          break;
        }
        case 'J': {
          color = {0.0f, 0.0f, 0.6f, 1.0f};
          break;
        }
        }
        BatchRenderer2D::draw_quad({x, y}, {quad_size, quad_size}, color);
      }
    }

    BatchRenderer2D::end_batch();

    OpenGLShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());
    BatchRenderer2D::flush();

    window->on_update();
  }
}

void Application::on_event(const Event &event) {
  LOG_INFO(event);

  Event::dispatch<KeyPressedEvent>(event, [this](const engine::KeyPressedEvent &key_press_event) {
    if (key_press_event.get_key_code() == engine::KeyCode::Escape) {
      this->running = false;
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

  // TODO: this should be somewhere else
  glViewport(0, 0, width, height);
}

} // namespace engine
