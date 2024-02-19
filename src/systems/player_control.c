#include "player_control.h"

#include <raylib.h>

#include "sprite.h"

void player_init(PlayerControlSystem_Player *player,
                 ResourceManagerSystem *resource_manager_system) {
    player->direction = RIGHT;
    player->state = WALK;
    player->can_move = true;

    player->uuid = new_uuid();

    player->sprite.position = (Vector2){40, 60};
    player->sprite.sprite_index = resource_manager_load_texture_file(
        resource_manager_system, "sprites/meatchunk.png");

    player->collider.position = (Vector2){40, 60};
    player->collider.velocity = (Vector2){1, 2};
    player->collider.size = (Vector2){48, 48};
    player->collider.acceleration = (Vector2){1, 1};
    player->collider.flags = 0;
}

void player_side_movement(PlayerControlSystem_Player *player) {
    if (IsKeyDown(KEY_A)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES LEFT MOVEMENT");
        if (player->can_move == true) {
            player->state = WALK;
            player->collider.position.x -= player->collider.velocity.x;
            player->sprite.position.x -= player->collider.velocity.x;
        }
        player->direction = LEFT;
        TraceLog(LOG_INFO, "PLAYER SUCCEEDED LEFT MOVEMENT");
    }
    if (IsKeyDown(KEY_D)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES RIGHT MOVEMENT");
        if (player->can_move == true) {
            player->state = WALK;
            player->collider.position.x += player->collider.velocity.x;
            player->sprite.position.x += player->collider.velocity.x;
            TraceLog(LOG_INFO, "PLAYER SUCCEEDED RIGHT MOVEMENT");
        }
        player->direction = RIGHT;
    }
}

void player_jump(PlayerControlSystem_Player *player) {
    if (IsKeyDown(KEY_SPACE)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES JUMP");
        if (player->can_move == true) {
            player->state = JUMP;
            player->collider.position.y += player->collider.velocity.y;
            player->sprite.position.y += player->collider.velocity.y;
            TraceLog(LOG_INFO, "PLAYER SUCCEEDED JUMP");
        }
    }
}

void player_control_system_update(PlayerControlSystem *sys,
                                  SpriteSystem *sprite_system) {
    for (size_t i = 0; i < sys->players.count; i++) {
        sprite_push(
            sprite_system,
            (Sprite_Info){
                .sprite_index = sys->players.items[i].sprite.sprite_index,
                .position =
                    (Vector2){.x = sys->players.items[i].sprite.position.x,
                              .y = sys->players.items[i].sprite.position.y}});
        sys->players.items[i].sprite.position = GetMousePosition();
        player_side_movement(&sys->players.items[i]);
        player_jump(&sys->players.items[i]);
    }
}
