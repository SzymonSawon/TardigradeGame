#include "debug_info.h"

#include <assert.h>
#include <raylib.h>

void debug_info_system_init(DebugInfoSystem* sys,
                            ResourceManagerSystem* resource_manager) {
    resource_manager_load_texture_file(resource_manager, "sprites/mage.png");

    sys->debug_sprite =
        resource_manager_get_sprite(resource_manager, "sprites/mage.png");
    assert(sys->debug_sprite);
}

void debug_info_system_update(DebugInfoSystem* sys,
                              SpriteSystem* sprite_system) {
    if (IsKeyPressed(KEY_F1)) {
        sys->visible = !sys->visible;
    }
    if (sys->visible) {
        DrawFPS(5, 5);
        sprite_push(sprite_system,
                    (Sprite_Info){.sprite_index = sys->debug_sprite,
                                  .position = (Vector2){.x = 20, .y = 40}});
    }
}
