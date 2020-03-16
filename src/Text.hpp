#pragma once
#ifndef A1FD79AD_8740_4EB9_8959_317F5CD3D21D
#define A1FD79AD_8740_4EB9_8959_317F5CD3D21D

namespace pacman {

// Helper for drawing a limited set of text messages.
class Text {
public:
  static void render_you_win(const Coord &position);
  static void render_you_lose(const Coord &position);
  static void render_press_p(const Coord &position);

private:
  static inline void render_y(const Coord &position, const Color &color);
  static inline void render_o(const Coord &position, const Color &color);
  static inline void render_u(const Coord &position, const Color &color);
  static inline void render_w(const Coord &position, const Color &color);
  static inline void render_i(const Coord &position, const Color &color);
  static inline void render_n(const Coord &position, const Color &color);
  static inline void render_l(const Coord &position, const Color &color);
  static inline void render_s(const Coord &position, const Color &color);
  static inline void render_e(const Coord &position, const Color &color);
  static inline void render_p(const Coord &position, const Color &color);
  static inline void render_r(const Coord &position, const Color &color);
};

} // namespace pacman

#endif /* A1FD79AD_8740_4EB9_8959_317F5CD3D21D */
