#ifndef SPRITE_H_
#define SPRITE_H_

#include <raylib.h>
#define spriteArraySize 10;

typedef struct Sprite {
    Texture2D spritesheet;
    int width;
    int height;
    Vector2 position;
} Sprite;

typedef struct SpriteSystem {
    Sprite *sprites[10];
    int currentSize;
} SpriteSystem;

void push_sprite(SpriteSystem *SpriteSystem, Sprite *sprite);
void render_sprites(SpriteSystem *SpriteSystem);

#endif
