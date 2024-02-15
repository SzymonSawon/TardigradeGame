#include "resource_manager.h"

#include <raylib.h>
#include <string.h>

void resource_manager_system_init(ResourceManagerSystem* sys,
                                  char* assets_path) {
    TraceLog(LOG_INFO, "Initializing ResourceManagerSystem!");
    sys->root_path = strdup(assets_path);

    // Empty sprite to allow 0 to indicate error
    da_append(sys->sprites, (ResourceManager_Sprite){0});
}

void resource_manager_system_update(ResourceManagerSystem* sys) {
    if (IsKeyPressed(KEY_F5)) {
        TraceLog(LOG_INFO, "Reloading ResourceManagerSystem!");
        // reload textures
        for (size_t i = 0; i < sys->texture_files.count; i++) {
            ResourceManager_TextureFile* file = &sys->texture_files.items[i];
            UnloadTexture(file->texture);
            file->texture = LoadTexture(
                TextFormat("%s/%s", sys->root_path, file->filename));
            for (size_t j = 0; j < sys->sprites.count; j++) {
                ResourceManager_Sprite* sprite = &sys->sprites.items[i];
                if (sprite->texture_index == i &&
                    strcmp(sprite->sprite_name, file->filename) == 0) {
                    sprite->source_rect = (Rectangle){
                        .x = 0,
                        .y = 0,
                        .width = file->texture.width,
                        .height = file->texture.height,
                    };
                }
            }
        }
    }
}

void resource_manager_system_deinit(ResourceManagerSystem* sys) {
    TraceLog(LOG_INFO, "Deinitializing ResourceManagerSystem!");
    for (size_t i = 0; i < sys->texture_files.count; i++) {
        ResourceManager_TextureFile* file = &sys->texture_files.items[i];
        UnloadTexture(file->texture);
    }
}

size_t resource_manager_load_texture_file(ResourceManagerSystem* sys,
                                          char* filename) {
    ResourceManager_TextureFile tex_file = {0};
    tex_file.filename = strdup(filename);
    tex_file.texture =
        LoadTexture(TextFormat("%s/%s", sys->root_path, filename));

    size_t texture_file_index = sys->texture_files.count;
    da_append(sys->texture_files, tex_file);

    ResourceManager_Sprite sprite = (ResourceManager_Sprite){
        .sprite_name = strdup(tex_file.filename),
        .source_rect =
            (Rectangle){
                .x = 0,
                .y = 0,
                .width = tex_file.texture.width,
                .height = tex_file.texture.height,
            },
        .texture_index = texture_file_index,
    };
    da_append(sys->sprites, sprite);

    return texture_file_index;
}

size_t resource_manager_load_spritesheet_file(ResourceManagerSystem* sys,
                                              char* filename, int rows,
                                              int columns) {
    ResourceManager_TextureFile tex_file = {0};
    tex_file.filename = strdup(filename);
    tex_file.texture =
        LoadTexture(TextFormat("%s/%s", sys->root_path, filename));

    size_t texture_file_index = sys->texture_files.count;
    da_append(sys->texture_files, tex_file);

    ResourceManager_Spritesheet spritesheet = (ResourceManager_Spritesheet){
        .spritesheet_name = strdup(tex_file.filename),
        .source_rect =
            (Rectangle){
                .x = 0,
                .y = 0,
                .width = tex_file.texture.width,
                .height = tex_file.texture.height,
            },
        .texture_index = texture_file_index,
        .rows = rows,
        .columns = columns,
    };
    da_append(sys->spritesheets, spritesheet);

    for (size_t i = 1; i <= spritesheet.columns; i++) {
        ResourceManager_Animation_Spritesheet single_animation =
            (ResourceManager_Animation_Spritesheet){
                .animation_index = texture_file_index + i,
                .animation_name = strdup(tex_file.filename)};
        for (size_t j = 1; j <= spritesheet.rows; j++) {
            ResourceManager_Sprite temp_sprite = (ResourceManager_Sprite){
                .sprite_name = strdup(tex_file.filename),
                .source_rect =
                    (Rectangle){
                        .x = 0,
                        .y = 0,
                        // assume correct values
                        .width = tex_file.texture.width / columns,
                        .height = tex_file.texture.height / rows,
                    },
                .texture_index = j,
            };
            da_append(single_animation, temp_sprite);
        }
    }

    return texture_file_index;
}

size_t resource_manager_get_sprite(ResourceManagerSystem* sys, char* name) {
    for (size_t i = 1; i < sys->sprites.count; i++) {
        if (strcmp(sys->sprites.items[i].sprite_name, name) == 0) {
            return i;
        }
    }

    return SPRITE_NOT_FOUND;
}
