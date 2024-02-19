#include "world.h"

#include <raylib.h>

#include "systems/player_control.h"
#include "systems/resource_manager.h"
#include "utils/ida.h"

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
    player_control_system_init(&world->player_system,
                               &world->resource_manager_system);

    // Add some colliders for tests
    for (size_t i = 0; i < 16; i++) {
        PhysicsSystem_Collider c = {
            .uuid = new_uuid(),
            .position = {.x = 10 * GetRandomValue(6, 40),
                         .y = 10 * GetRandomValue(3, 10)},
            .size = {.x = 10 * GetRandomValue(1, 3),
                     .y = 10 * GetRandomValue(1, 3)},
        };
        if (GetRandomValue(1, 100) < 30) {
            c.flags |= PSCF_NOGRAVITY | PSCF_STATIC;
        }
        if (GetRandomValue(1, 100) < 10) {
            c.flags |= PSCF_NOSOLID;
        }
        ida_append(world->physics_system.colliders, c);
        assert(ida_find(world->physics_system.colliders, c.uuid));
    }

    // player test
    PlayerControlSystem_Player player = player_create(&world->physics_system);
    ida_append(world->player_system.players, player);
}

void world_update(World* world) {
    {
        // updating systems
        resource_manager_system_update(&world->resource_manager_system);
        player_control_system_update(&world->player_system,
                                     &world->sprite_system,
                                     &world->physics_system);
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
