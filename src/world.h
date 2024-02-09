#ifndef WORLD_H_
#define WORLD_H_

#include <raylib.h>

#include "systems/debug_info.h"
#include "systems/resource_manager.h"

typedef struct {
    DebugInfoSystem debug_info_system;
    ResourceManagerSystem resource_manager_system;
    SpriteSystem sprite_system;
} World;

void world_init(World*);
void world_update(World*);
void world_deinit(World*);

#endif
