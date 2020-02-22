#include "pch.hpp"

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main() {
  engine::Logger::init("pacman.log");

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    LOG_CRITICAL("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

  glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_CRITICAL("Failed to initialize GLAD");
    return -1;
  }

  LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));
  LOG_INFO("OpenGL vendor: {}", glGetString(GL_VENDOR));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
