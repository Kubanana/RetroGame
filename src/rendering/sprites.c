#include "sprites.h"

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

void convert_sprite_to_argb(uint32_t* sprite, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        uint32_t c = sprite[i];

        uint8_t r = (c >> 24) & 0xFF;
        uint8_t g = (c >> 16) & 0xFF;
        uint8_t b = (c >> 8) & 0xFF;
        uint8_t a = (c >> 0) & 0xFF;

        sprite[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }
}