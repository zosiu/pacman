#include "engine/OpenGL/OpenGLShaderProgram.hpp"
#include "engine/core/Core.hpp"
#include "engine/core/Window.hpp"
#include "engine/events/Event.hpp"
#include "engine/events/KeyEvents.hpp"
#include "engine/utils/OrthographicCamera.hpp"
#include "pch.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main() {
  engine::Logger::init("pacman.log");

  auto window = std::make_unique<engine::Window>(engine::WindowProps("pacman", SCR_WIDTH, SCR_HEIGHT));

  bool running = true;

  window->set_event_callback([&running](const engine::Event &event) {
    LOG_INFO(event);

    engine::Event::dispatch<engine::KeyPressedEvent>(event, [&running](const engine::KeyPressedEvent &key_press_event) {
      if (key_press_event.get_key_code() == engine::KeyCode::Escape) {
        running = false;
      }
    });
  });

  float vertices[] = {
      0.25f,  0.25f,  0.0f, 1.0f, 0.0f, 0.0f, //
      0.25f,  -0.25f, 0.0f, 0.0f, 1.0f, 1.0f, //
      -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, //
      -0.25f, 0.25f,  0.0f, 1.0f, 1.0f, 1.0f  //
  };

  unsigned int indices[] = {
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
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

  engine::OrthographicCamera camera(-1.0f, 1.0f, -1.0f, 1.0f);
  camera.set_rotation(45.0f);
  camera.set_position({0.1f, -0.5f, 0.0f});
  program.upload_mat4_unifom("u_view_projection", camera.get_view_projection_matrix());

  while (running) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window->on_update();
  }

  return 0;
}
