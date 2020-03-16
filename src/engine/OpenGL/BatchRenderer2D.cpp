#include "../../pch.hpp"

#include <glad/glad.h>

#include "BatchRenderer2D.hpp"

namespace engine {

static constexpr size_t max_quad_count = 1000;
static constexpr size_t max_vertex_count = max_quad_count * 4;
static constexpr size_t max_index_count = max_quad_count * 6;

struct Vertex {
  glm::vec3 position;
  glm::vec4 color;
};

struct RendererData {
  GLuint quad_vertex_array;
  GLuint quad_vertex_buffer;
  GLuint quad_index_buffer;

  size_t index_count = 0;

  Vertex *quads = nullptr;
  Vertex *quads_iter = nullptr;
};

static RendererData data;

void BatchRenderer2D::init() {
  data.quads = new Vertex[max_vertex_count];

  glGenVertexArrays(1, &data.quad_vertex_array);
  glBindVertexArray(data.quad_vertex_array);

  uint32_t indices[max_index_count];

  for (auto [i, offset] = std::pair<size_t, size_t>(0, 0); i < max_index_count; i += 6, offset += 4) {
    // every quad is composed of 2 triangles
    indices[i + 0] = offset + 0; // top-left
    indices[i + 1] = offset + 1; // top-right
    indices[i + 2] = offset + 2; // bottom-left

    indices[i + 3] = offset + 2; // bottom-left
    indices[i + 4] = offset + 3; // bottom-right
    indices[i + 5] = offset + 1; // top-right
  }

  glGenBuffers(1, &data.quad_index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.quad_index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glGenBuffers(1, &data.quad_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, data.quad_vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, max_vertex_count * sizeof(Vertex), nullptr, GL_STREAM_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, color));
  glEnableVertexAttribArray(1);
}

void BatchRenderer2D::destroy() {
  glDeleteVertexArrays(1, &data.quad_vertex_array);
  glDeleteBuffers(1, &data.quad_vertex_buffer);
  glDeleteBuffers(1, &data.quad_index_buffer);

  delete[] data.quads;
}

void BatchRenderer2D::begin_batch() { data.quads_iter = data.quads; }

void BatchRenderer2D::end_batch() {
  // stream the vertices to the GPU
  glBindBuffer(GL_ARRAY_BUFFER, data.quad_vertex_buffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0, (data.quads_iter - data.quads) * sizeof(Vertex), data.quads);
}

void BatchRenderer2D::flush() {
  // one draw call per batch
  glBindVertexArray(data.quad_vertex_array);
  glDrawElements(GL_TRIANGLES, data.index_count, GL_UNSIGNED_INT, nullptr);

  data.index_count = 0;
}

void BatchRenderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
  if (data.index_count >= max_index_count) {
    end_batch();
    flush();
    begin_batch();
  }

  // store all 4 vertices of the quad
  data.quads_iter->position = {position.x, position.y, 0.0f}; // top-left
  data.quads_iter->color = color;
  ++data.quads_iter;

  data.quads_iter->position = {position.x + size.x, position.y, 0.0f}; // top-right
  data.quads_iter->color = color;
  ++data.quads_iter;

  data.quads_iter->position = {position.x, position.y + size.y, 0.0f}; // bottom-left
  data.quads_iter->color = color;
  ++data.quads_iter;

  data.quads_iter->position = {position.x + size.x, position.y + size.y, 0.0f}; // bottom-right
  data.quads_iter->color = color;
  ++data.quads_iter;

  data.index_count += 6;
}

} // namespace engine
