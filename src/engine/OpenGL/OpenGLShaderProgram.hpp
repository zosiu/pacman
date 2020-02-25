#pragma once

#ifndef FEC30CDA_0134_3B0A_1280_9930933A4E77
#define FEC30CDA_0134_3B0A_1280_9930933A4E77

#include <glad/glad.h>

namespace engine {
class OpenGLShaderProgram {
public:
  OpenGLShaderProgram(const char *vertex_shader_filename, const char *fragment_shader_filename);
  ~OpenGLShaderProgram();

  void bind() const;
  void unbind() const;

private:
  GLuint compile_shader(GLenum shader_type, const char *source_file);

private:
  GLuint id = 0;
};
} // namespace engine

#endif /* FEC30CDA_0134_3B0A_1280_9930933A4E77 */