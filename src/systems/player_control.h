#ifndef PLAYER_CONTROL_H_
#define PLAYER_CONTROL_H_

#include <raylib.h>

#include "../utils/ida.h"
#include "physics.h"
#include "resource_manager.h"
#include "sprite.h"

typedef struct {
    size_t uuid;
    size_t collider;
    enum {
        PSDPD_LEFT,
        PCSPD_RIGHT,
    } direction;
    enum {
        PCSPS_WALK,
        PCSPS_JUMP,
        PCSPS_DODGE,
    } state;
    bool can_move;
} PlayerControlSystem_Player;

typedef struct {
    ida_list(PlayerControlSystem_Player);
} PlayerControlSystem_Players;

typedef struct {
    PlayerControlSystem_Players players;
    size_t player_sprite;
} PlayerControlSystem;

PlayerControlSystem_Player player_create(PhysicsSystem *physics_system);

void player_control_system_init(PlayerControlSystem *sys,
                                ResourceManagerSystem *resource_manager);
void player_control_system_update(PlayerControlSystem *sys,
                                  SpriteSystem *sprite_system,
                                  PhysicsSystem *physics_system);

#endif
