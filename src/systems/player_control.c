#include "player_control.h"

#include <raylib.h>

#include "sprite.h"

const float PLAYER_SPEED = 100;
const float PLAYER_BREAKING = 0.8;
const float PLAYER_JUMP = 100;

PlayerControlSystem_Player player_create(PhysicsSystem *physics_system) {
    PhysicsSystem_Collider c = {
        .uuid = new_uuid(),
        .position = {40, 60},
        .size = {48, 48},
    };
    ida_append(physics_system->colliders, c);

    PlayerControlSystem_Player player = {
        .direction = PCSPD_RIGHT,
        .state = PCSPS_WALK,
        .can_move = true,
        .uuid = new_uuid(),
        .collider = c.uuid,
    };

    return player;
}

static void player_side_movement(PlayerControlSystem_Player *player,
                                 PhysicsSystem_Collider *c) {
    c->velocity.x *= PLAYER_BREAKING;
    if (IsKeyDown(KEY_A)) {
        if (player->can_move == true) {
            player->state = PCSPS_WALK;
            c->velocity.x = -PLAYER_SPEED;
        }
        player->direction = PSDPD_LEFT;
    }
    if (IsKeyDown(KEY_D)) {
        if (player->can_move == true) {
            player->state = PCSPS_WALK;
            c->velocity.x = PLAYER_SPEED;
        }
        player->direction = PCSPD_RIGHT;
    }
}

static void player_jump(PlayerControlSystem_Player *player,
                        PhysicsSystem_Collider *c) {
    if (IsKeyPressed(KEY_SPACE)) {
        if (player->can_move == true) {
            player->state = PCSPS_JUMP;
            c->velocity.y = -PLAYER_JUMP;
        }
    }
}

void player_control_system_init(PlayerControlSystem *sys,
                                ResourceManagerSystem *resource_manager) {
    resource_manager_load_texture_file(resource_manager,
                                       "sprites/meatchunk.png");
    sys->player_sprite =
        resource_manager_get_sprite(resource_manager, "sprites/meatchunk.png");
}

void player_control_system_update(PlayerControlSystem *sys,
                                  SpriteSystem *sprite_system,
                                  PhysicsSystem *physics_system) {
    for (size_t i = 0; i < sys->players.count; i++) {
        PhysicsSystem_Collider *c =
            ida_find(physics_system->colliders, sys->players.items[i].collider);
        assert(c);
        player_side_movement(&sys->players.items[i], c);
        player_jump(&sys->players.items[i], c);
        sprite_push(sprite_system,
                    (Sprite_Info){.sprite_index = sys->player_sprite,
                                  .position = c->position});
    }
}
