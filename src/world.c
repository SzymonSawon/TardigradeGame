#include "world.h"

#include <raylib.h>

void world_init(World* world) {
    TraceLog(LOG_INFO, "Initializing World!");
    *world = (World){
        .debug_info_system = {.visible = true},
        .physics_system =
            {
                .bounding_rect = {.width = 500, .height = 400},
                .gravity = {.y = 100, .x = 10},
            },
    };
    resource_manager_system_init(&world->resource_manager_system, "assets");
    debug_info_system_init(&world->debug_info_system,
                           &world->resource_manager_system,
                           &world->physics_system);

    // Add some colliders for tests
    {
        PhysicsSystem_Collider c = {
            .uuid = new_uuid(),
            .position = {.x = 60, .y = 40},
            .size = {.x = 20, .y = 30},
        };
        ida_append(world->physics_system.colliders, c);
    }
    {
        PhysicsSystem_Collider c = {
            .uuid = new_uuid(),
            .position = {.x = 100, .y = 40},
            .size = {.x = 20, .y = 30},
        };
        ida_append(world->physics_system.colliders, c);
    }
    {
        PhysicsSystem_Collider c = {
            .uuid = new_uuid(),
            .position = {.x = 40, .y = 140},
            .size = {.x = 60, .y = 20},
        };
        ida_append(world->physics_system.colliders, c);
    }
    {
        PhysicsSystem_Collider c = {
            .uuid = new_uuid(),
            .position = {.x = 100, .y = 140},
            .size = {.x = 60, .y = 20},
        };
        ida_append(world->physics_system.colliders, c);
    }
}

void world_update(World* world) {
    {
        // updating systems
        resource_manager_system_update(&world->resource_manager_system);
        physics_system_update(&world->physics_system);
    }

    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        // drawing systems
        debug_info_system_update(&world->debug_info_system,
                                 &world->sprite_system, &world->physics_system);
        sprite_system_update(&world->sprite_system,
                             &world->resource_manager_system);
    }
    EndDrawing();
}

void world_deinit(World* world) {
    TraceLog(LOG_INFO, "Deinitializing World!");
    resource_manager_system_deinit(&world->resource_manager_system);
}
