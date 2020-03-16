#include <glm/gtc/type_ptr.hpp>

#include "../utils/Assert.hpp"
#include "../utils/File.hpp"

#include "ShaderProgram.hpp"

namespace engine {

ShaderProgram::ShaderProgram(const char *vertex_shader_filename, const char *fragment_shader_filename) {
  GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_filename);
  REFUTE(vertex_shader == 0, "failed to create vertex shader");

  GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_filename);
  REFUTE(fragment_shader == 0, "failed to create fragment shader");

  const GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);

  glLinkProgram(shader_program);

  GLint linking_result;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &linking_result);

  if (linking_result == GL_FALSE) {
    GLchar log_message[1024];
    glGetProgramInfoLog(shader_program, 1024, nullptr, log_message);
    LOG_ERROR("[SHADER] linking failed: {}", log_message);

    glDeleteProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
  } else {
    glValidateProgram(shader_program);

    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    id = shader_program;
    REFUTE(shader_program == 0, "failed to create shader program");
  }
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(id); }

void ShaderProgram::bind() const { glUseProgram(id); }

void ShaderProgram::unbind() const { glUseProgram(0); }

void ShaderProgram::upload_view_projection_uniform(const glm::mat4 &matrix) {
  GLint current_program;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
  REFUTE(current_program == 0, "could not find active shader program");

  GLint uniform_location = glGetUniformLocation(current_program, "u_view_projection");
  REFUTE(uniform_location == -1, "could not find uniform u_view_projection");

  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::upload_model_transformation_uniform(const glm::mat4 &matrix) {
  GLint current_program;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
  REFUTE(current_program == 0, "could not find active shader program");

  GLint uniform_location = glGetUniformLocation(current_program, "u_model_transformation");
  REFUTE(uniform_location == -1, "could not find uniform u_model_transformation");

  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::upload_mat4_unifom(const std::string &name, const glm::mat4 &matrix) {
  GLint uniform_location = glGetUniformLocation(id, name.c_str());
  REFUTE(uniform_location == -1, "could not find uniform {}", name);
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint ShaderProgram::compile_shader(GLenum shader_type, const char *source_file) {
  GLuint shader = glCreateShader(shader_type);
  std::string file_contents = File::contents(source_file);
  const char *shader_source = file_contents.c_str();
  glShaderSource(shader, 1, &shader_source, nullptr);
  glCompileShader(shader);

  GLint compilation_result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_result);

  if (compilation_result == GL_FALSE) {
    GLchar log_message[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, log_message);
    LOG_ERROR("[SHADER] compilation failed: {}", log_message);
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

} // namespace engine
