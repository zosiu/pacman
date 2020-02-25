#include "OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) {
  recalculate_matrices();
}

void OrthographicCamera::set_projection(float left, float right, float bottom, float top) {
  projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  recalculate_matrices();
}

const glm::vec3 &OrthographicCamera::get_position() const { return position; }

void OrthographicCamera::set_position(const glm::vec3 &new_position) {
  position = new_position;
  recalculate_matrices();
}

float OrthographicCamera::get_rotation() const { return rotation_in_degrees; }

void OrthographicCamera::set_rotation(float new_rotation) {
  rotation_in_degrees = new_rotation;
  recalculate_matrices();
}

const glm::mat4 &OrthographicCamera::get_view_projection_matrix() const { return view_projection_matrix; }

void OrthographicCamera::recalculate_matrices() {
  glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) *
                             glm::rotate(glm::mat4(1.0f), glm::radians(rotation_in_degrees), glm::vec3(0, 0, 1));
  view_matrix = glm::inverse(transformation);
  view_projection_matrix = projection_matrix * view_matrix;
}

} // namespace engine
