#include "game.h"

float posX = 50;
float posY = 50;

Direction playerDirection = DIR_DOWN;

int frame = 0;
float animationTimer = 0;

Sprite sprite1;
Sprite brick_tile;

void run()
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool running = true;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer("Cool", WIDTH * 3, HEIGHT * 3,
         SDL_WINDOW_RESIZABLE, &window, &renderer);

    SDL_SetRenderLogicalPresentation(renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
         SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    uint32_t* frameBuffer = (uint32_t*)malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    
    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastFrame = lastTime;
    int frames = 0;
    float fps = 0.0f;
    
    sprite1 = load_sprite("assets/Sprite-0002.png");
    brick_tile = load_sprite("assets/Bricks.png");

    int tilemap[MAP_HEIGHT][MAP_WIDTH] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    while (running)
    {
        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTime) / 1000.0f;
        lastTime = now;

        frames++;

        if (now - lastFrame >= 1000)
        {
            fps = frames * 1000.0f / (now - lastFrame);
            frames = 0;
            lastFrame = now;
        }

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) running = false;
            
            if (event.type == SDL_EVENT_KEY_DOWN)
            {

            }
        }

        const bool* state = SDL_GetKeyboardState(NULL);

        int speed = 100;

        float x = 0;
        float y = 0;

        if (state[SDL_SCANCODE_W]) y -= speed;
        if (state[SDL_SCANCODE_S]) y += speed;
        if (state[SDL_SCANCODE_D]) x += speed;
        if (state[SDL_SCANCODE_A]) x -= speed;

        if (state[SDL_SCANCODE_W]) playerDirection = DIR_UP;
        if (state[SDL_SCANCODE_S]) playerDirection = DIR_DOWN;
        if (state[SDL_SCANCODE_D]) playerDirection = DIR_RIGHT;
        if (state[SDL_SCANCODE_A]) playerDirection = DIR_LEFT;

        posX += x * delta;
        posY += y * delta;

        animationTimer += delta;

        if (animationTimer >= 0.15f)
        {
            animationTimer = 0.0f;
            frame = (frame + 1) % FRAMES_PER_DIR;
        }

        clear(frameBuffer, 0xFF90D5FF);
        draw_tilemap(frameBuffer, &brick_tile, tilemap);
        draw_sprite(frameBuffer, &sprite1, 100, 100, 3);
        draw_sprite(frameBuffer, player_sprite, (int)posX, (int)posY, 2);
        draw_player(frameBuffer, (int)posX, (int)posY, 2, playerDirection, frame);
        draw_text(frameBuffer, "START GAME", 10, 10, 0xFFFFFFFF);

        char fps_text[16];
        sprintf(fps_text, "%.0f FPS", fps);

        draw_text(frameBuffer, fps_text, 200, 10, 0xFFFFFFFF);


        SDL_UpdateTexture(texture, NULL, frameBuffer, WIDTH * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(frameBuffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();;
}