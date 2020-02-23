#pragma once

#ifndef C1DF43B1_3134_3B08_1451_71D02759082F
#define C1DF43B1_3134_3B08_1451_71D02759082F

struct GLFWwindow;

namespace engine {

class OpenGLContext {
public:
  OpenGLContext(GLFWwindow *window_handle);

  void init();
  void swap_buffers();

private:
  GLFWwindow *glfw_window_handle;
};

} // namespace engine

#endif /* C1DF43B1_3134_3B08_1451_71D02759082F */
