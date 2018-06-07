//
// Created by David on 21/05/2017.
//

#include "globals.h"

//--- globals
SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_DisplayMode g_displaymode;
SDL_Rect g_viewport;


SDL_Color g_black;
SDL_Color g_white;

// 0: full FPS, 1: cap the framerate
int g_draw_mode = 1;
static Uint32 g_next_time;

t_game *g_game = NULL;

t_menu *g_currentMenu = NULL;

void setGame(t_game *p_game) {

    if (g_game != NULL);
    free(g_game);
    g_game = p_game;
}

t_game *getGame(){
    return g_game;
}

SDL_Window *getWindow() {
    return g_window;
}

void setWindow(SDL_Window *p_window) {
    g_window = p_window;
}

SDL_Renderer *getRenderer() {
    return g_renderer;
}

void setRenderer(SDL_Renderer *p_renderer) {
    g_renderer = p_renderer;
}

//int *getChannels() {
//    return g_channels;
//}

t_menu *getCurrentMenu() {
    return g_currentMenu;
}

void setCurrentMenu(t_menu *p_menu) {
    g_currentMenu = p_menu;
}

SDL_Rect *getViewPort() {
    return &g_viewport;
}

int getDrawMode() {
    return g_draw_mode;
}

SDL_Color *getWhite() {
    return &g_white;
}

SDL_Color *getBlack() {
    return &g_black;
}

Uint32 getNextTime() {
    return g_next_time;
}

void setNextTime(Uint32 p_nextTime) {
    g_next_time = p_nextTime;
}

SDL_DisplayMode *getDisplayMode() {
    return &g_displaymode;
}