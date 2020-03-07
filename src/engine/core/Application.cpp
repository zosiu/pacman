#include "../../pch.hpp"

#include "../OpenGL/ShaderProgram.hpp"
#include "../events/KeyEvents.hpp"

#include <GLFW/glfw3.h>

#include "Application.hpp"

namespace engine {

Application::Application(const std::string &window_name, uint16_t width, uint16_t height) {
  window = std::make_unique<Window>(WindowProps(window_name, width, height));
  window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));

  float aspect_ratio = (float)width / (float)height;
  camera = std::make_unique<OrthographicCamera>(-aspect_ratio, aspect_ratio, -1.0, 1.0);
}

void Application::attach_layer(Layer *layer) {
  layers.push_back(layer);
  layer->on_attach();
}

void Application::run() {
  ShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());

  last_frame_time = glfwGetTime();
  srand(last_frame_time);
  double now_time = 0;
  double delta_ms = 0;

  while (running) {
    now_time = glfwGetTime();
    delta_ms = (now_time - last_frame_time) * 1000;
    last_frame_time = now_time;

    for (auto layer : layers)
      layer->on_update(delta_ms);

    window->on_update();
  }
}

void Application::on_event(const Event &event) {
  Event::dispatch<KeyPressedEvent>(event, [this](const engine::KeyPressedEvent &key_press_event) {
    if (key_press_event.get_key_code() == engine::KeyCode::Escape ||
        key_press_event.get_key_code() == engine::KeyCode::Q) {
      this->running = false;
    }
  });

  Event::dispatch<WindowClosedEvent>(event, std::bind(&Application::on_window_close, this, std::placeholders::_1));
  Event::dispatch<WindowResizedEvent>(event, std::bind(&Application::on_window_resize, this, std::placeholders::_1));

  for (auto layer : layers)
    layer->on_event(event);
}

void Application::on_window_close(const WindowClosedEvent & /* event */) { running = false; }

void Application::on_window_resize(const WindowResizedEvent &event) {
  uint16_t width = event.get_width();
  uint16_t height = event.get_height();

  float aspect_ratio = (float)width / (float)height;
  camera->set_projection(-aspect_ratio, aspect_ratio, -1.0f, 1.0f);
  ShaderProgram::upload_view_projection_uniform(camera->get_view_projection_matrix());
  glViewport(0, 0, width, height);
}

} // namespace engine
