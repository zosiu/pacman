#include "Application.hpp"
#include "../OpenGL/OpenGLShaderProgram.hpp"
#include "../OpenGL/renderer/BatchRenderer2D.hpp"
#include "../events/KeyEvents.hpp"
#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

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

  constexpr int num_of_quads = 21;
  constexpr float t = 2.0f / num_of_quads;
  const auto model_transform =
      glm::mat4({{t, 0.0f, 0.0f, 0.0f}, {0.0f, -t, 0.0f, 0.0f}, {0.0f, 0.0f, t, 0.0f}, {-1.0, 1.0, -1.0, 1.0}});

  constexpr char level_layout[num_of_quads][num_of_quads] = {
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.'},
      {'.', '#', 'O', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'O', '#', '.'},
      {'.', '#', 'o', '#', '#', 'o', '#', '#', '#', 'o', '#', 'o', '#', '#', '#', 'o', '#', '#', 'o', '#', '.'},
      {'.', '#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#', '.'},
      {'.', '#', 'o', '#', '#', 'o', '#', 'o', '#', 'o', '#', 'o', '#', 'o', '#', 'o', '#', '#', 'o', '#', '.'},
      {'.', '#', 'o', 'o', 'o', 'o', '#', 'o', 'o', 'o', '#', 'o', 'o', 'o', '#', 'o', 'o', 'o', 'o', '#', '.'},
      {'.', '#', '#', '#', '#', 'o', '#', '#', '#', 'o', '#', 'o', '#', '#', '#', 'o', '#', '#', '#', '#', '.'},
      {'.', '.', '.', '.', '#', 'o', '#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#', 'o', '#', '.', '.', '.', '.'},
      {'#', '#', '#', '#', '#', 'o', '#', 'o', '#', '#', 'J', '#', '#', 'o', '#', 'o', '#', '#', '#', '#', '#'},
      {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#', 'J', 'J', 'J', '#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
      {'#', '#', '#', '#', '#', 'o', '#', 'o', '#', '#', '#', '#', '#', 'o', '#', 'o', '#', '#', '#', '#', '#'},
      {'.', '.', '.', '.', '#', 'o', '#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#', 'o', '#', '.', '.', '.', '.'},
      {'.', '#', '#', '#', '#', 'o', '#', '#', '#', 'o', '#', 'o', '#', '#', '#', 'o', '#', '#', '#', '#', '.'},
      {'.', '#', 'o', 'o', 'o', 'o', '#', 'o', 'o', 'o', '#', 'o', 'o', 'o', '#', 'o', 'o', 'o', 'o', '#', '.'},
      {'.', '#', 'o', '#', '#', 'o', '#', 'o', '#', 'o', '#', 'o', '#', 'o', '#', 'o', '#', '#', 'o', '#', '.'},
      {'.', '#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#', '.'},
      {'.', '#', 'o', '#', '#', 'o', '#', '#', '#', 'o', '#', 'o', '#', '#', '#', 'o', '#', '#', 'o', '#', '.'},
      {'.', '#', 'O', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'O', '#', '.'},
      {'.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};

  const glm::vec2 size = {1.0, 1.0};
  const glm::vec2 small_pill_size = {0.2, 0.2};
  const glm::vec2 big_pill_size = {0.4, 0.4};
  const glm::vec2 psize = {1.0, 1.0};

  while (running) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    BatchRenderer2D::begin_batch();

    for (int dy = 0; dy < num_of_quads; ++dy) {
      for (int dx = 0; dx < num_of_quads; ++dx) {
        // glm::vec3 transformed = transform * glm::vec3{dx, dy, 1.0f};
        glm::vec2 pos = {dx, dy};

        switch (level_layout[dy][dx]) {
        case '#': {
          BatchRenderer2D::draw_quad(pos, size, {0.0f, 0.0f, 0.5f, 1.0f});
          break;
        }
        case '.': {
          BatchRenderer2D::draw_quad(pos, size, {0.0f, 0.0f, 0.0f, 1.0f});
          break;
        }
        case 'o': {
          BatchRenderer2D::draw_quad(pos, size, {0.0f, 0.0f, 0.0f, 1.0f});
          BatchRenderer2D::draw_quad(pos, small_pill_size, {1.0f, 1.0f, 1.0f, 1.0f});
          break;
        }
        case 'O': {
          BatchRenderer2D::draw_quad(pos, size, {0.0f, 0.0f, 0.0f, 1.0f});
          BatchRenderer2D::draw_quad(pos, big_pill_size, {1.0f, 1.0f, 1.0f, 1.0f});
          break;
        }
        case 'J': {
          BatchRenderer2D::draw_quad(pos, size, {0.0f, 0.0f, 0.3f, 1.0f});
          break;
        }
        }
      }
    }

    BatchRenderer2D::draw_quad({10, 12}, psize, {1.0f, 1.0f, 0.0f, 1.0f});

    BatchRenderer2D::end_batch();

    OpenGLShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());
    OpenGLShaderProgram::upload_model_transformation_uniform(model_transform);

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
