#include <globals.h>
#include <game/menuTree/menu.h>
#include <network/server.h>
#include "mainLoop.h"

void quit(int rc);

int initSDL();

int main(int argc, char *argv[]) {

    if (initSDL() == EXIT_SUCCESS) {
        SDL_Log("SDL init with succes\n");
    };

    initMainMenu();
    runGame();

    return (EXIT_SUCCESS);
}

int initSDL() {

//    t_genericList *l_textureList = createList();
//    t_genericList *l_fontList = createList();
//
//    setFontList(l_fontList);
//    setTextureList(l_textureList);

    getBlack()->r = 0;
    getBlack()->g = 0;
    getBlack()->b = 0;
    getBlack()->r = 255;
    getBlack()->g = 255;
    getBlack()->b = 255;

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s \n", SDL_GetError());
        quit(EXIT_FAILURE);
    }

    // Display available audio device
    int count = SDL_GetNumAudioDevices(0), i;
    for (i = 0; i < count; ++i) {
        fprintf(stderr, "Audio device %d: %s\n", i, SDL_GetAudioDeviceName(i, 0));
    }

    // Get desktop information
    if (SDL_GetDesktopDisplayMode(0, getDisplayMode()) < 0) {
        fprintf(stderr, "Could not get display mode: %s\n", SDL_GetError());
        quit(EXIT_FAILURE);
    }

    getViewPort()->x = 0;
    getViewPort()->y = 0;
    getViewPort()->w = COMMON_MIN(getDisplayMode()->w, WINDOWS_WIDTH);
    getViewPort()->h = COMMON_MIN(getDisplayMode()->h, WINDOWS_HEIGHT);

    // Create an application window with the following settings:
    SDL_Window *l_window;
    l_window = SDL_CreateWindow(
            "Game",                    //    window title
            SDL_WINDOWPOS_UNDEFINED,           //    initial x destination
            SDL_WINDOWPOS_UNDEFINED,           //    initial y destination
            getViewPort()->w,                        //    width, in pixels
            getViewPort()->h,                        //    height, in pixels
            SDL_WINDOW_SHOWN                   //    flags
    );

    // Check that the window was successfully made
    if (l_window == NULL) {
        // In the event that the window could not be made...
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        quit(1);
    }
    setWindow(l_window);
    SDL_Renderer *l_renderer;
    l_renderer = SDL_CreateRenderer(l_window, -1, 0); // SDL_RENDERER_PRESENTVSYNC
    if (l_renderer < 0) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        quit(EXIT_FAILURE);
    }

    setRenderer(l_renderer);
    SDL_RenderGetViewport(l_renderer, getViewPort());
    if (TTF_Init() == -1) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s \n", TTF_GetError());
        quit(EXIT_FAILURE);
    }

    t_game *game = malloc(sizeof(t_game));
    if (!game) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate gamestate memeory\n");
        return EXIT_FAILURE;
    }

    game->isMatchmaking = false;
    game->inParty = false;
    game->nbConnected = 0;
    setGame(game);

    return (EXIT_SUCCESS);
}

Uint32 timeLeft() {
    Uint32 now, l_nextTime;
    now = SDL_GetTicks();
    l_nextTime = getNextTime();
    if (l_nextTime <= now)
        return 0;
    else
        return l_nextTime - now;
}

void capFramerate() {
    Uint32 l_nextTime = getNextTime();
    SDL_Delay(timeLeft());
    l_nextTime += TICK_INTERVAL;
    setNextTime(l_nextTime);
}

void quit(int rc) {

    printf("Cleanup\n");

//    t_listElement *l_listElement;
//
//    for (l_listElement = getTextureList()->first; l_listElement != NULL; l_listElement = l_listElement->next) {
//        printf("Destroy texture\n");
//        SDL_DestroyTexture((SDL_Texture *) l_listElement->data);
//    }
//    destroyList(getTextureList());
//
//    for (l_listElement = getFontList()->first; l_listElement != NULL; l_listElement = l_listElement->next) {
//        printf("Destroy font\n");
//        TTF_CloseFont((TTF_Font *) l_listElement->data);
//    }
//    destroyList(getFontList());

    if (getRenderer()) {
        SDL_DestroyRenderer(getRenderer());
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s\n", SDL_GetError());
    }
    if (getWindow()) {
        SDL_DestroyWindow(getWindow());
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s\n", SDL_GetError());
    }
    end();
    SDL_Quit();
    SDL_Log("Exit game\n");
    exit(rc);
}