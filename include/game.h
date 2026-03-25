#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <SDL3/SDL.h>

#include "renderer.h"

#include "font.h"
#include "sprites.h"
#include "tiles.h"

#define WIDTH 256
#define HEIGHT 256

typedef enum
{
    DIR_DOWN,
    DIR_RIGHT,
    DIR_UP,
    DIR_LEFT
} Direction;

void run();

#endif