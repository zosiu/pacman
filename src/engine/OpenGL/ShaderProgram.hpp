#pragma once

#ifndef FEC30CDA_0134_3B0A_1280_9930933A4E77
#define FEC30CDA_0134_3B0A_1280_9930933A4E77

#include <glad/glad.h>

namespace engine {
class ShaderProgram {
public:
  ShaderProgram(const char *vertex_shader_filename, const char *fragment_shader_filename);
  ~ShaderProgram();

  void bind() const;
  void unbind() const;

  static void upload_view_projection_uniform(const glm::mat4 &matrix);
  static void upload_model_transformation_uniform(const glm::mat4 &matrix);
  void upload_mat4_unifom(const std::string &name, const glm::mat4 &matrix);

private:
  inline GLuint compile_shader(GLenum shader_type, const char *source_file);

private:
  GLuint id = 0;
};
} // namespace engine

#endif /* FEC30CDA_0134_3B0A_1280_9930933A4E77 */
