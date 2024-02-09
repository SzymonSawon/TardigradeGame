#include "sprite.h"
//a

void PushSprite(SpriteSystem *SpriteSystem, Sprite *sprite){
  SpriteSystem->sprites[SpriteSystem->currentSize] = sprite;
  SpriteSystem->currentSize++;
  TraceLog(LOG_INFO, "Sprite added successfully");
}

void RenderSprites(SpriteSystem *SpriteSystem){
  for(int i=0;i<SpriteSystem->currentSize;i++){
    DrawTexture(SpriteSystem->sprites[i]->spritesheet, SpriteSystem->sprites[i]->position.x, SpriteSystem->sprites[i]->position.y, WHITE);
  }
  TraceLog(LOG_INFO, "Sprite rendered");
  SpriteSystem->sprites[0] = '\0';
  SpriteSystem->currentSize = 0;
  TraceLog(LOG_INFO, "Sprites removed");
}
