#include "Application.hpp"
#include "../OpenGL/OpenGLShaderProgram.hpp"
#include "../events/KeyEvents.hpp"
#include <glad/glad.h>

namespace engine {

Application::Application(uint16_t width, uint16_t height) {
  window = std::make_unique<Window>(WindowProps("Application", width, height));
  window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
  float aspect_ratio = (float)width / (float)height;
  camera = std::make_unique<OrthographicCamera>(-aspect_ratio, aspect_ratio, -1.0, 1.0);
}

void Application::run() {
  float vertices[] = {
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, //
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, //
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f  //
  };

  unsigned int indices[] = {
      0, 1, 3, //
      1, 2, 3  //
  };

  unsigned int VBO, VAO;
  unsigned int EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  engine::OpenGLShaderProgram program("shaders/base.vert.glsl", "shaders/base.frag.glsl");
  program.bind();

  while (running) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    OpenGLShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
