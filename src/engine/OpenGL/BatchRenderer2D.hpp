#pragma once

#ifndef B3313634_D134_3B0D_1651_64583BB067DE
#define B3313634_D134_3B0D_1651_64583BB067DE

namespace engine {

// Batch rendeder for drawing multiple quads with a single draw call
class BatchRenderer2D {
public:
  static void init();
  static void destroy();

  static void begin_batch();
  static void end_batch();
  static void flush();

  static void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
};

} // namespace engine

#endif /* B3313634_D134_3B0D_1651_64583BB067DE */
