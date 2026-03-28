#include "game.h"
#include <stdlib.h>

Sprite player_sprite;

Sprite sprite1;
Sprite brick_tile;
Sprite boss;

static MIX_Mixer* mixer = NULL;
static MIX_Audio* music = NULL;
static MIX_Track* track = NULL;

void play_music(const char* filePath)
{   
    SDL_AudioDeviceID devid = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    mixer = MIX_CreateMixerDevice(devid, NULL);
    music = MIX_LoadAudio(mixer, filePath, true);
    track = MIX_CreateTrack(mixer);

    MIX_SetTrackAudio(track, music);
    MIX_SetTrackGain(track, 0.2f);

    SDL_PropertiesID properties = SDL_CreateProperties();
    SDL_SetNumberProperty(properties, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
    SDL_SetNumberProperty(properties, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, 200);

    MIX_PlayTrack(track, properties);

    SDL_DestroyProperties(properties);
}

void run()
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool running = true;

    Player player = { 50, 50, DIR_DOWN, ANIM_IDLE, 0, 0 };

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    MIX_Init();

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
    
    player_sprite = load_sprite("assets/16x16 Idle-Sheet.png");

    sprite1 = load_sprite("assets/Sprite-0002.png");
    brick_tile = load_sprite("assets/Bricks.png");
    boss = load_sprite("assets/ScaryBoss.png");

    play_music("assets/bosstheme.ogg");

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

        if (state[SDL_SCANCODE_W]) player.direction = DIR_UP;
        if (state[SDL_SCANCODE_S]) player.direction = DIR_DOWN;
        if (state[SDL_SCANCODE_D]) player.direction = DIR_RIGHT;
        if (state[SDL_SCANCODE_A]) player.direction = DIR_LEFT;

        player.posX += x * delta;
        player.posY += y * delta;

        player.animationTimer += delta;

        if (player.animationTimer >= 0.25f)
        {
            player.animationTimer = 0.0f;
            player.frame = (player.frame + 1) % 4;
        }

        clear(frameBuffer, 0xFF90D5FF);
        draw_tilemap(frameBuffer, &brick_tile, tilemap);
        draw_sprite(frameBuffer, &sprite1, 100, 100, 3);
        draw_player(frameBuffer, &player_sprite, &player, 2);
        draw_text(frameBuffer, "START GAME", 10, 10, 0xFFFFFFFF);
        draw_sprite(frameBuffer, &boss, 100, 20, 2);

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