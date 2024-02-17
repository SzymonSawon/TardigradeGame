#include "player_control.h"

#include <raylib.h>

void player_side_movement(Player_Info *player) {
    if (IsKeyDown(KEY_A)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES LEFT MOVEMENT");
        if (player->can_move == true) {
            player->state = WALK;
            player->position.x -= player->movement_speed;
        }
        player->direction = LEFT;
        TraceLog(LOG_INFO, "PLAYER SUCCEEDED LEFT MOVEMENT");
    }
    if (IsKeyDown(KEY_D)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES RIGHT MOVEMENT");
        if (player->can_move == true) {
            player->state = WALK;
            player->position.x += player->movement_speed;
            TraceLog(LOG_INFO, "PLAYER SUCCEEDED RIGHT MOVEMENT");
        }
        player->direction = RIGHT;
    }
}

void player_jump(Player_Info *player) {
    if (IsKeyDown(KEY_SPACE)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES JUMP");
        if (player->can_move == true) {
            player->state = JUMP;
            player->position.y -= player->jump_force;
            TraceLog(LOG_INFO, "PLAYER SUCCEEDED JUMP");
        }
    }
}

// should be added to abilities, because it needs cooldown system
void player_dodge(Player_Info *player) {
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        TraceLog(LOG_INFO, "PLAYER INITIATES DODGE");
        if (player->can_move == true) {
            player->state = DODGE;
            if (player->direction == RIGHT) {
                player->position.x += player->dodge_speed;
                TraceLog(LOG_INFO, "PLAYER SUCCEEDED DODGE RIGHT");
            } else if (player->direction == LEFT) {
                player->position.x -= player->dodge_speed;
                TraceLog(LOG_INFO, "PLAYER SUCCEEDED DODGE LEFT");
            }
        }
    }
}
