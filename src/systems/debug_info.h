#ifndef DEBUG_INFO_H_
#define DEBUG_INFO_H_

#include <stdbool.h>

#include "physics.h"
#include "sprite.h"

typedef struct {
    bool visible;
    size_t debug_sprite;
} DebugInfoSystem;

void debug_info_system_init(DebugInfoSystem* sys,
                            ResourceManagerSystem* resource_manager);

void debug_info_system_update(DebugInfoSystem* sys, SpriteSystem* sprite_system,
                              PhysicsSystem* physics_system);

#endif
