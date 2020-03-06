#pragma once

#ifndef A183409F_A75D_4B50_81DE_1D279D10F4E4
#define A183409F_A75D_4B50_81DE_1D279D10F4E4

#include "engine/core/Layer.hpp"
#include "engine/events/KeyEvents.hpp"
#include "engine/OpenGL/OpenGLShaderProgram.hpp"
#include "Player.hpp"
#include "Ghost.hpp"
#include "Level.hpp"

namespace pacman {

enum class GameState { Paused, InProgress, Won, Lost };

class GameLayer : public engine::Layer {
public:
  GameLayer();
  ~GameLayer() override;

  void on_attach() override;
  void on_update(float time_since_last_update_in_ms) override;
  void on_event(const engine::Event &event) override;

private:
  void update(float time_since_last_update_in_ms);
  void render() const;
  void on_key_pressed(const engine::KeyPressedEvent &event);

private:
  std::unique_ptr<engine::OpenGLShaderProgram> shader;

  GameState game_state = GameState::Paused;
  Level level_map;
  std::unique_ptr<Player> player;
  std::vector<Ghost> ghosts;
};

} // namespace pacman

#endif /* A183409F_A75D_4B50_81DE_1D279D10F4E4 */
