#include <raylib.h>

#include "world.h"

int main(void) {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");
    world_init();

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        world_update();
    }

    world_deinit();
    CloseWindow();

    return 0;
}
