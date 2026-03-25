#ifndef SPRITES_H
#define SPRITES_H

#include <stdint.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define PLAYER_DIRECTIONS 3
#define FRAMES_PER_DIR 4

typedef struct
{
  uint32_t* pixels;
  int width;
  int height;
} Sprite;

Sprite load_sprite(const char* path);

#endif