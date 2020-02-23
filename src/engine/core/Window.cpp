#include "Window.hpp"

namespace engine {
static uint8_t window_count = 0;

Window::Window(const WindowProps &props) : props(props) { create(props); }

Window::~Window() { destroy(); }

unsigned int Window::get_width() const { return props.width; }
unsigned int Window::get_height() const { return props.height; }
GLFWwindow *Window::get_native_window() const { return native_window; }

void Window::create(const WindowProps &props) {
  LOG_INFO("[create window] {} ({}x{})", props.title, props.width, props.height);
  if (window_count == 0) {
    [[maybe_unused]] int glfw_init_success = glfwInit();
    ASSERT(glfw_init_success, "failed to intialize GLFW");

    glfwSetErrorCallback([](int error_code, const char *error_message) {
      LOG_ERROR("[GLFW Error] {} : {}", error_code, error_message);
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MINIMUM_OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINIMUM_OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  }

  native_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
  REFUTE(native_window == nullptr, "Failed to create GLFW window");
  ++window_count;
}

void Window::destroy() {
  glfwDestroyWindow(native_window);

  --window_count;
  if (window_count == 0) {
    glfwTerminate();
  }
}

} // namespace engine
