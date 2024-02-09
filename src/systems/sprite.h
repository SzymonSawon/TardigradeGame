#ifndef SPRITE_H_
#define SPRITE_H_

#include <raylib.h>

#include "../utils/da.h"
#include "resource_manager.h"

typedef struct {
    size_t sprite_index;
    Vector2 position;
} Sprite_Info;

typedef struct {
    da_list(Sprite_Info);
} Sprite_Infos;

typedef struct {
    Sprite_Infos sprites;
} SpriteSystem;

void sprite_system_update(SpriteSystem *sys,
                          ResourceManagerSystem *resource_manager);

void sprite_push(SpriteSystem *sys, Sprite_Info sprite);

#endif
