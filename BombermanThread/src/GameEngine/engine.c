/*
** engine.c for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 10:12 2017 dyoubi
** Last update 23 mai 10:12 2017 dyoubi
*/

#include <sharde.h>
#include "GameEngine/engine.h"
#include "defs.h"

int initEngine(t_game_engine *p_game_engine) {
    SDL_DisplayMode displayMode = {
            SDL_PIXELFORMAT_RGBA32,
            WINDOWS_WIDTH,
            WINDOWS_HEIGHT,
            0,
            0
    };
    // Initialiser SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s \n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s \n", SDL_GetError());
    };

    // Get desktop information
    if (SDL_GetDesktopDisplayMode(0, &displayMode) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize display mode: %s \n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    // Create an application window with the following settings:
    SDL_Window *l_window;
    l_window = SDL_CreateWindow(
            "Bomberman",                    //    window title
            SDL_WINDOWPOS_UNDEFINED,           //    initial x destination
            SDL_WINDOWPOS_UNDEFINED,           //    initial y destination
            WINDOWS_WIDTH,                        //    width, in pixels
            WINDOWS_HEIGHT,                        //    height, in pixels
            SDL_WINDOW_SHOWN                   //    flags
    );

    // Check that the window was successfully made
    if (l_window == NULL) {
        // In the event that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize create window: %s \n", SDL_GetError());
        return (EXIT_FAILURE);
    }
    SDL_Renderer *l_renderer;
    l_renderer = SDL_CreateRenderer(l_window, -1, 0); // SDL_RENDERER_PRESENTVSYNC
    if (l_renderer < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize renderer: %s \n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    p_game_engine->window = l_window;
    p_game_engine->renderer = l_renderer;

    return EXIT_SUCCESS;
}

int cleanEngine(t_game_engine *p_game_engine) {

    if (p_game_engine->renderer) {
        SDL_DestroyRenderer(p_game_engine->renderer);
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s\n", SDL_GetError());
    }

    if (p_game_engine->window) {
        SDL_DestroyWindow(p_game_engine->window);
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "%s\n", SDL_GetError());
    }

    //TODO: Surveiller que toutes les ressources SDL sont netoyer

    return (EXIT_SUCCESS);
}

SDL_Texture *TextureFromText(char *p_text, TTF_Font *p_font, SDL_Color p_color) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    if (strcmp(p_text, "") != 0) {
        surface = TTF_RenderText_Solid(p_font, p_text, p_color);
        pthread_mutex_lock(&g_game.mutex);
        texture = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
        pthread_mutex_unlock(&g_game.mutex);
    }

    SDL_FreeSurface(surface);
    return texture;
}

void drawInputText(char *p_input_text, int p_x, int p_y) {
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Rect dest = {10, 10, 0, 0,};
    SDL_Color white = {255, 255, 255, 255};


    if (strcmp(p_input_text, "") != 0) {
        if ((font = TTF_OpenFont("ressources/fonts/upheavtt.ttf", 32)) == NULL) {
            perror("Impossible d'ouvrir la texture\n");
            return;
        }

        texture = TextureFromText(p_input_text, font, white);
        if (texture) {
            SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

            pthread_mutex_lock(&g_game.mutex);
            SDL_RenderCopy(g_game_engine.renderer, texture, NULL, &dest);
            pthread_mutex_unlock(&g_game.mutex);
            SDL_DestroyTexture(texture);
        }
        TTF_CloseFont(font);
    }
}

//void capFramerate() {
//    Uint32 l_nextTime = getNextTime();
//    SDL_Delay(timeLeft());
//    l_nextTime += TICK_INTERVAL;
//    setNextTime(l_nextTime);
//}
//
//Uint32 timeLeft() {
//    Uint32 now, l_nextTime;
//    now = SDL_GetTicks();
//    l_nextTime = getNextTime();
//    if (l_nextTime <= now)
//        return 0;
//    else
//        return l_nextTime - now;
//}