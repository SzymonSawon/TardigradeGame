#include "world.h"

#include <raylib.h>

void world_init(void) { TraceLog(LOG_INFO, "Initializing World!"); }

void world_update(void) {
    {
        // updating systems
    }

    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        DrawText("Unnamed Tardigrade Game", 30, 20, 20, LIGHTGRAY);
        // drawing systems
    }
    EndDrawing();
}

void world_deinit(void) { TraceLog(LOG_INFO, "Deinitializing World!"); }
