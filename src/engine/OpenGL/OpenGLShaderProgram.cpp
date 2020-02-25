#include "OpenGLShaderProgram.hpp"
#include "../core/Core.hpp"
#include "../utils/File.hpp"

namespace engine {

OpenGLShaderProgram::OpenGLShaderProgram(const char *vertex_shader_filename, const char *fragment_shader_filename) {
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
    GLint linking_log_length;
    glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &linking_log_length);
    char *log_message = (char *)alloca((size_t)linking_log_length * sizeof(char));
    glGetProgramInfoLog((GLuint)linking_result, linking_log_length, &linking_log_length, log_message);
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

OpenGLShaderProgram::~OpenGLShaderProgram() { glDeleteProgram(id); }

void OpenGLShaderProgram::bind() const { glUseProgram(id); }

void OpenGLShaderProgram::unbind() const { glUseProgram(0); }

GLuint OpenGLShaderProgram::compile_shader(GLenum shader_type, const char *source_file) {
  GLuint shader = glCreateShader(shader_type);
  std::string file_contents = File::contents(source_file);
  const char *shader_source = file_contents.c_str();
  glShaderSource(shader, 1, &shader_source, nullptr);
  glCompileShader(shader);

  GLint compilation_result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_result);

  if (compilation_result == GL_FALSE) {
    GLsizei compilation_log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &compilation_log_length);
    char *log_message = (char *)alloca((size_t)compilation_log_length * sizeof(char));
    glGetShaderInfoLog((GLuint)compilation_result, compilation_log_length, &compilation_log_length, log_message);
    LOG_ERROR("[SHADER] compilation failed: {}", log_message);
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

} // namespace engine
