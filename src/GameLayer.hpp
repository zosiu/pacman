#pragma once

#ifndef A183409F_A75D_4B50_81DE_1D279D10F4E4
#define A183409F_A75D_4B50_81DE_1D279D10F4E4

#include "Ghost.hpp"
#include "Level.hpp"
#include "Player.hpp"

#include "engine/OpenGL/ShaderProgram.hpp"
#include "engine/core/Layer.hpp"
#include "engine/events/Event.hpp"
#include "engine/events/KeyEvents.hpp"

namespace pacman {

enum class GameState { Paused, InProgress, Won, Lost };

// Layer that pulls all the game elements together:
// Responsible for creating and managing:
// * the level
// * the player
// * the ghosts
// * the game state (in_progress, paused, won, lost)
// * responding to keyboard events
//   * setting player direction
//   * pause/resume/restart the game

class GameLayer : public engine::Layer {
public:
  GameLayer();
  ~GameLayer() override;
  GameLayer(const GameLayer &) = delete;
  GameLayer(GameLayer &&) = delete;
  GameLayer &operator=(const GameLayer &) = delete;
  GameLayer &operator=(GameLayer &&) = delete;

  void on_attach() override;
  void on_update(float time_since_last_update_in_ms) override;
  void on_event(const engine::Event &event) override;

private:
  inline void reset();
  inline void update(float time_since_last_update_in_ms);
  inline void render() const;
  void on_key_pressed(const engine::KeyPressedEvent &event);

private:
  struct GhostAttrs {
    Color color;
    TileCoord starting_position;
    Direction starting_direction;
    GhostBehaviourType behaviour;
    Ghost::TargetFun target_fun;
  };

  inline std::unordered_map<std::string, GhostAttrs> ghosts_config() const;

private:
  std::unique_ptr<engine::ShaderProgram> shader;

  GameState game_state = GameState::Paused;
  Level level_map;
  std::unique_ptr<Player> player;
  std::unordered_map<std::string, std::unique_ptr<Ghost>> ghosts;
};

} // namespace pacman

#endif /* A183409F_A75D_4B50_81DE_1D279D10F4E4 */
