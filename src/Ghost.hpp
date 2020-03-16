#pragma once

#ifndef G280C0FF_2134_3B70_DE3E_712C7D9F7AC9
#define G280C0FF_2134_3B70_DE3E_712C7D9F7AC9

#include "Agent.hpp"
#include "Direction.hpp"
#include "GhostBehaviour.hpp"
#include "Movement.hpp"

namespace pacman {

// Ghost agent:
// * movement is determinded by a given behaviour and target tile
class Ghost : public Agent {

public:
  using TargetFun = std::function<TileCoord()>;

  Ghost(Coord starting_position, Direction starting_direction, float speed, const Level *level, //
        Color Color);

  void set_target_function(const TargetFun &fun);
  void set_behaviour(GhostBehaviourType type);
  void render() const override;

private:
  bool can_move_into(Tile tile) const;
  void after_move(const MoveInfo &info);
  Direction next_direction(const DirectionInfo &info) const;
  inline void render_body() const;
  inline void render_pupils() const;
  inline void render_eye_whites() const;

private:
  Color color;
  GhostBehaviour behaviour = GhostBehaviourType::Random;
  TileCoord default_target;
  TargetFun calculate_target;
};

} // namespace pacman

#endif /* G280C0FF_2134_3B70_DE3E_712C7D9F7AC9 */
