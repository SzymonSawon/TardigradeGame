#include "sprite.h"

void sprite_system_update(SpriteSystem *sys,
                          ResourceManagerSystem *resource_manager) {
    for (int i = 0; i < sys->sprites.count; i++) {
        ResourceManager_Sprite sprite =
            resource_manager->sprites.items[sys->sprites.items[i].sprite_index];
        Rectangle target = {
            .x = sys->sprites.items[i].position.x,
            .y = sys->sprites.items[i].position.y,
            .width = sprite.source_rect.width,
            .height = sprite.source_rect.height,
        };
        DrawTexturePro(
            resource_manager->texture_files.items[sprite.texture_index].texture,
            sprite.source_rect, target, (Vector2){0}, 0, WHITE);
    }
    TraceLog(LOG_DEBUG, "Sprite rendered");
    sys->sprites.count = 0;
    TraceLog(LOG_DEBUG, "Sprites removed");
}

void sprite_push(SpriteSystem *sys, Sprite_Info sprite) {
    da_append(sys->sprites, sprite);
    TraceLog(LOG_DEBUG, "Sprite added successfully");
}
