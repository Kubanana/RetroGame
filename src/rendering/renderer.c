#include "renderer.h"
#include "sprites.h"
#include "font.h"

void put_pixel(uint32_t* frameBuffer, int x, int y, uint32_t color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        frameBuffer[y * WIDTH + x] = color;
    }
}

void clear(uint32_t* frameBuffer, uint32_t color)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        frameBuffer[i] = color;
    }
}

void draw_square(uint32_t* frameBuffer, int x, int y, int size, uint32_t color)
{
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            put_pixel(frameBuffer, x + i, y + j, color);
        }
    }
}

void draw_char(uint32_t* frameBuffer, char c, int x, int y, uint32_t color)
{
    uint8_t* pattern = NULL;

    if (c >= 'A' && c <= 'Z')
    {
        pattern = font[c - 'A'];
    }

    else if (c >= '0' && c <= '9')
    {
        pattern = font_numbers[c - '0'];
    }

    else return;
    
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (pattern[row] & (1 << (4 - col)))
            {
                frameBuffer[(y + row) * WIDTH + (x + col)] = color;
            }
        }
    }
}

void draw_text(uint32_t* frameBuffer, const char* text, int x, int y, uint32_t color)
{
    int cursor = 0;
    while (*text)
    {
        if ((*text >= 'A' && *text <= 'Z') || (*text >= '0' && *text <= '9'))
        {
            draw_char(frameBuffer, *text, x + cursor*6, y, color);
        }

        cursor++;
        text++;
    }
}

void draw_sprite(uint32_t* frameBuffer, Sprite* sprite, int x, int y, int scale)
{
    for (int j = 0; j < sprite->height; j++)
    {
        for (int i = 0; i < sprite->width; i++)
        {
            uint32_t color = sprite->pixels[j * sprite->width + i];

            if ((color >> 24) == 0) continue;

            for (int sy = 0; sy < scale; sy++)
            {
                for (int sx = 0; sx < scale; sx++)
                {
                    int px = x + i * scale + sx;
                    int py = y + j * scale + sy;

                    frameBuffer[py * WIDTH + px] = color;
                }
            }
        }
    }
}

void draw_player(uint32_t* frameBuffer, int x, int y, int scale, int direction, int frame)
{
    int directionIndex = 0;

    switch (direction)
    {
        case DIR_DOWN: directionIndex = 0; break;
        case DIR_RIGHT: directionIndex = 1; break;
        case DIR_UP: directionIndex = 2; break;
        case DIR_LEFT: directionIndex = 1; break;
    }

    int frameIndex = (directionIndex * FRAMES_PER_DIR + frame) * 16 * 16;
    
    int flip = (direction == DIR_LEFT);

    for (int j = 0; j < 16; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            int srcX = flip ? (16 - 1 - i) : i;

            uint32_t color = player_sprite[frameIndex + j * 16 + srcX];
            if ((color >> 24) == 0) continue;

            for (int sy = 0; sy < scale; sy++)
            {
                for (int sx = 0; sx < scale; sx++)
                {
                    int px = x + i * scale + sx;
                    int py = y + j * scale + sy;

                    frameBuffer[py * WIDTH + px] = color;
                }
            }
        }
    }
}

void draw_tilemap(uint32_t* frameBuffer, Sprite* sprite, int tilemap[MAP_HEIGHT][MAP_WIDTH])
{
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            int tile = tilemap[row][col];

            if (tile == 0) continue;

            int x = col * TILE_SIZE;
            int y = row * TILE_SIZE;

            draw_sprite(frameBuffer, sprite, x, y, 1);
        }
    }
}