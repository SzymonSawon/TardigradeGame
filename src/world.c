#include "world.h"

#include <raylib.h>

void world_init(World* world) {
    TraceLog(LOG_INFO, "Initializing World!");
    *world = (World){.debug_info_system = {.visible = false}};
}

void world_update(World* world) {
    {
        // updating systems
    }

    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        
        // drawing systems
        debug_info_system_update(&world->debug_info_system);
    }
    EndDrawing();
}

void world_deinit(World* world) { TraceLog(LOG_INFO, "Deinitializing World!"); }
