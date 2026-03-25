#include "sprites.h"
#include <stdlib.h>

Sprite load_sprite(const char* path)
{
    Sprite sprite;

    SDL_Surface* surface = IMG_Load(path);

    SDL_Surface* formattedSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ABGR8888);
    SDL_DestroySurface(surface);

    sprite.width = formattedSurface->w;
    sprite.height = formattedSurface->h;

    int size = sprite.width * sprite.height;
    sprite.pixels = malloc(size * sizeof(uint32_t));

    memcpy(sprite.pixels, formattedSurface->pixels, size * sizeof(uint32_t));

    SDL_DestroySurface(formattedSurface);

    return sprite;
}