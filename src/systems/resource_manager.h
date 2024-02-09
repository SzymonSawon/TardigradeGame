#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <raylib.h>

#include "../utils/da.h"

#define SPRITE_NOT_FOUND 0

typedef struct {
    char* filename;
    Texture texture;
} ResourceManager_TextureFile;

typedef struct {
    da_list(ResourceManager_TextureFile);
} ResourceManager_TextureFiles;

typedef struct {
    char* sprite_name;
    size_t texture_index;
    Rectangle source_rect;
} ResourceManager_Sprite;

typedef struct {
    da_list(ResourceManager_Sprite);
} ResourceManager_Sprites;

typedef struct {
    char* root_path;
    ResourceManager_TextureFiles texture_files;
    ResourceManager_Sprites sprites;
} ResourceManagerSystem;

void resource_manager_system_init(ResourceManagerSystem* sys,
                                  char* assets_path);

void resource_manager_system_update(ResourceManagerSystem* sys);

void resource_manager_system_deinit(ResourceManagerSystem* sys);

size_t resource_manager_load_texture_file(ResourceManagerSystem* sys,
                                          char* filename);

size_t resource_manager_get_sprite(ResourceManagerSystem* sys, char* name);

#endif
