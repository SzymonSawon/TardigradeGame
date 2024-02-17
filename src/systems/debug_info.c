#include "debug_info.h"

#include <assert.h>
#include <raylib.h>
#include <raymath.h>

void debug_info_system_init(DebugInfoSystem* sys,
                            ResourceManagerSystem* resource_manager,
                            PhysicsSystem* physics_system) {
    resource_manager_load_texture_file(resource_manager, "sprites/mage.png");

    sys->debug_sprite =
        resource_manager_get_sprite(resource_manager, "sprites/mage.png");
    assert(sys->debug_sprite);

    sys->debug_collider = new_uuid();

    {
        PhysicsSystem_Collider c = {
            .uuid = sys->debug_collider,
            .position = {.x = 60, .y = 40},
            .size = {.x = 10, .y = 10},
        };
        ida_append(physics_system->colliders, c);
    }
}

void debug_info_system_update(DebugInfoSystem* sys, SpriteSystem* sprite_system,
                              PhysicsSystem* physics_system) {
    if (IsKeyPressed(KEY_F1)) {
        sys->visible = !sys->visible;
    }
    if (sys->visible) {
        DrawFPS(5, 5);
        sprite_push(sprite_system,
                    (Sprite_Info){.sprite_index = sys->debug_sprite,
                                  .position = (Vector2){.x = 20, .y = 40}});
        DrawRectangleLinesEx(physics_system->bounding_rect, 1, BLUE);
        for (size_t i = 0; i < physics_system->colliders.count; i++) {
            DrawRectangleLines(physics_system->colliders.items[i].position.x,
                               physics_system->colliders.items[i].position.y,
                               physics_system->colliders.items[i].size.x,
                               physics_system->colliders.items[i].size.y,
                               GREEN);
        }

        {  // have some fun with collider
            PhysicsSystem_Collider* c =
                ida_find(physics_system->colliders, sys->debug_collider);
            assert(c);

            c->velocity = Vector2Scale(
                Vector2Subtract(GetMousePosition(), c->position), 10);
        }
    }
}
