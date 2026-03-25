#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "game.h"
#include "sprites.h"
#include "tiles.h"

#define MAP_WIDTH 16
#define MAP_HEIGHT 16

void put_pixel(uint32_t* frameBuffer, int x, int y, uint32_t color);
void clear(uint32_t* frameBuffer, uint32_t color);
void draw_square(uint32_t* frameBuffer, int x, int y, int size, uint32_t color);
void draw_char(uint32_t* frameBuffer, char c, int x, int y, uint32_t color);
void draw_text(uint32_t* frameBuffer, const char* text, int x, int y, uint32_t color);
void draw_sprite(uint32_t* frameBuffer, Sprite* sprite, int x, int y, int scale);
void draw_player(uint32_t* frameBuffer, int x, int y, int scale, int direction, int frame);
void draw_tilemap(uint32_t* frameBuffer, Sprite* sprite, int tilemap[MAP_HEIGHT][MAP_WIDTH]);

#endif