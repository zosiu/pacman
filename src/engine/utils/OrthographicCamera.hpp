#pragma once

#ifndef A52A8786_F134_3B0A_1626_212C667E4E6B
#define A52A8786_F134_3B0A_1626_212C667E4E6B

namespace engine {

class OrthographicCamera {
public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void set_projection(float left, float right, float bottom, float top);

  const glm::vec3 &get_position() const;
  void set_position(const glm::vec3 &new_position);

  float get_rotation() const;
  void set_rotation(float new_rotation);

  const glm::mat4 &get_view_projection_matrix() const;

private:
  void recalculate_matrices();

private:
  glm::mat4 view_matrix = glm::mat4(1.0);
  glm::mat4 projection_matrix;
  glm::mat4 view_projection_matrix;

  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  float rotation_in_degrees = 0.0f;
};

} // namespace engine

#endif /* A52A8786_F134_3B0A_1626_212C667E4E6B */
