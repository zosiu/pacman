#include "OpenGLContext.hpp"
#include "../core/Core.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace engine {

OpenGLContext::OpenGLContext(GLFWwindow *window_handle) : glfw_window_handle(window_handle) {
  REFUTE(glfw_window_handle == nullptr, "nullptr glfw window in OpenGLContext");
}

void OpenGLContext::init() {
  glfwMakeContextCurrent(glfw_window_handle);
  [[maybe_unused]] int glad_init_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  ASSERT(glad_init_success, "failed to intialize GLAD");

  LOG_INFO("[OpenGL vendor] {0}", glGetString(GL_VENDOR));
  LOG_INFO("[OpenGL renderer] {0}", glGetString(GL_RENDERER));
  LOG_INFO("[OpenGL version] {0}", glGetString(GL_VERSION));
}

void OpenGLContext::swap_buffers() { glfwSwapBuffers(glfw_window_handle); }

} // namespace engine
