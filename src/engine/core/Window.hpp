#pragma once

#ifndef C4C12B61_3134_3B08_1762_7729EE37435C
#define C4C12B61_3134_3B08_1762_7729EE37435C

#include "../OpenGL/OpenGLContext.hpp"
#include "../events/Event.hpp"

struct GLFWwindow;

namespace engine {

struct WindowProps {
  std::string title;
  uint16_t width;
  uint16_t height;

  WindowProps(const std::string &title = "a window", uint16_t width = 800, uint16_t height = 600)
      : title(title), width(width), height(height) {}
};

class Window {
public:
  using EventCallbackFun = std::function<void(const Event &)>;

  Window(const WindowProps &props);
  ~Window();
  Window(const Window &) = delete;
  Window(Window &&) = delete;
  Window &operator=(const Window &) = delete;
  Window &operator=(Window &&) = delete;

  void on_update();

  unsigned int get_width() const;
  unsigned int get_height() const;
  GLFWwindow *get_native_window() const;
  void set_event_callback(const EventCallbackFun &callback);

private:
  void create(const WindowProps &props);
  void destroy();

  void register_window_closed_callback();
  void register_window_resized_callback();
  void register_key_callback();

private:
  GLFWwindow *native_window;
  std::unique_ptr<OpenGLContext> openGL_context;

  struct WindowData {
    std::string title;
    unsigned int width;
    unsigned int height;

    EventCallbackFun handle_event;
  };

  WindowData props;
};
} // namespace engine

#endif /* C4C12B61_3134_3B08_1762_7729EE37435C */
