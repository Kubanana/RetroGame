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

void draw_sprite_frame(uint32_t* frameBuffer, Sprite* sprite, int srcX, int srcY, int frameW, int frameH, int x, int y, int scale)
{
    for (int j = 0; j < frameH; j++)
    {
        for (int i = 0; i < frameW; i++)
        {
            uint32_t color = sprite->pixels[(srcY + j) * sprite->width + (srcX + i)];

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

void draw_player(uint32_t* frameBuffer, Sprite* sprite, Player* player, int scale)
{
    const int FRAME_W = 16;
    const int FRAME_H = 16;

    int row = player->state * 4 + player->direction;

    int srcX = player->frame * FRAME_W;
    int srcY = row * FRAME_H;

    draw_sprite_frame(frameBuffer, sprite, srcX, srcY, FRAME_W, FRAME_H, (int)player->posX, (int)player->posY, scale);
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