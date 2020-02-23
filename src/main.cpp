#include "engine/core/Core.hpp"
#include "engine/core/Window.hpp"
#include "pch.hpp"
#include <GLFW/glfw3.h>

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main() {
  engine::Logger::init("pacman.log");
  auto window = std::make_unique<engine::Window>(engine::WindowProps("pacman", SCR_WIDTH, SCR_HEIGHT));

  GLFWwindow *native_window = window->get_native_window();

  glfwMakeContextCurrent(native_window);
  glfwSetFramebufferSizeCallback(native_window,
                                 [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

  glfwSetKeyCallback(native_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    ASSERT(false, "Failed to initialize GLAD");
    return -1;
  }

  LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));
  LOG_INFO("OpenGL vendor: {}", glGetString(GL_VENDOR));

  while (!glfwWindowShouldClose(native_window)) {
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(native_window);
    glfwPollEvents();
  }

  return 0;
}
