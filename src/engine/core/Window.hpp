#pragma once

#ifndef C4C12B61_3134_3B08_1762_7729EE37435C
#define C4C12B61_3134_3B08_1762_7729EE37435C

#include "Core.hpp"
#include <GLFW/glfw3.h>

namespace engine {

struct WindowProps {
  std::string title;
  unsigned int width;
  unsigned int height;

  WindowProps(const std::string &title = "a window", unsigned int width = 800, unsigned int height = 600)
      : title(title), width(width), height(height) {}
};

class Window {
public:
  Window(const WindowProps &props);
  ~Window();
  Window(const Window &) = delete;
  Window(Window &&) = delete;
  Window &operator=(const Window &) = delete;
  Window &operator=(Window &&) = delete;

  unsigned int get_width() const;
  unsigned int get_height() const;
  GLFWwindow *get_native_window() const;

private:
  void create(const WindowProps &props);
  void destroy();

private:
  GLFWwindow *native_window;
  WindowProps props;
};
} // namespace engine

#endif /* C4C12B61_3134_3B08_1762_7729EE37435C */
