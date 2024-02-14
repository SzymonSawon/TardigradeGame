#ifndef PLAYER_CONTROL_H_
#define PLAYER_CONTROL_H_

#include <raylib.h>

#include "../utils/da.h"
#include "resource_manager.h"


typedef struct {
  int movement_speed;
  int dodge_speed;
  int jump_force;
  Vector2 position;
  enum {
  LEFT,
  RIGHT,
  } direction;
  enum {
  WALK,
  JUMP,
  DODGE,
  } state;
  bool can_move;
} Player_Info;

void player_side_movement(Player_Info *player);
void player_jump(Player_Info *player);
void player_dodge(Player_Info *player);


#endif
