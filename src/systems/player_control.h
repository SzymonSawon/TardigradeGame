#ifndef PLAYER_CONTROL_H_
#define PLAYER_CONTROL_H_

#include <raylib.h>

#include "../utils/ida.h"
#include "physics.h"
#include "resource_manager.h"
#include "sprite.h"

typedef struct {
    PhysicsSystem_Collider collider;
    Sprite_Info sprite;
    size_t uuid;
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
} PlayerControlSystem_Player;

typedef struct {
    ida_list(PlayerControlSystem_Player);
} PlayerControlSystem_Players;

typedef struct {
    PlayerControlSystem_Players players;
} PlayerControlSystem;

void player_side_movement(PlayerControlSystem_Player *player);
void player_jump(PlayerControlSystem_Player *player);
void player_init(PlayerControlSystem_Player *player,
                 ResourceManagerSystem *resource_manager);
void player_control_system_update(PlayerControlSystem *sys,
                                  SpriteSystem *sprite_system);

#endif
