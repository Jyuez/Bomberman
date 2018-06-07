//
// Created by David on 21/05/2017.
//

#ifndef BOMBERCLIENT_GLOBALS_H
#define BOMBERCLIENT_GLOBALS_H

#include "definitions.h"

typedef struct s_menu t_menu;
typedef struct s_menu_item t_menu_item;
typedef struct s_client_request t_client_request;
typedef struct s_player_infos t_player_infos;
typedef struct s_map t_map;
typedef struct s_game t_game;


int *getChannels();

int getDrawMode();

void setRenderer(SDL_Renderer *p_renderer);

void setWindow(SDL_Window *p_window);

void setNextTime(Uint32);

void setCurrentMenu(t_menu *p_menu);

void setGame(t_game *p_game);

void quit(int rc);

Uint32 getNextTime();

SDL_Rect *getViewPort();

SDL_Color *getBlack();

SDL_Color *getWhite();

SDL_Window *getWindow();

SDL_Renderer *getRenderer();

SDL_DisplayMode *getDisplayMode();

t_menu *getCurrentMenu();

t_game *getGame();

#endif //BOMBERCLIENT_GLOBALS_H
