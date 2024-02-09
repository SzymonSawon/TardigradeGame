#include <raylib.h>

#include "world.h"

int main(void) {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    World world = {0};
    world_init(&world);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        world_update(&world);
    }

    world_deinit(&world);
    CloseWindow();

    return 0;
}
