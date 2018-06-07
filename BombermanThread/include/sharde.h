/*
** sharde.h for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 10:40 2017 dyoubi
** Last update 23 mai 10:40 2017 dyoubi
*/

#ifndef BOMBERMAN_SHARDE_H
#define BOMBERMAN_SHARDE_H

#ifndef BOMBERMAN_STRUCTS_H
#include "structs.h"
#endif

#ifdef MAIN_FILE
t_game_engine g_game_engine;
t_game g_game;
t_game_mode g_game_mode;
#else
extern t_game_engine g_game_engine;
extern t_game g_game;
extern t_game_mode g_game_mode;
#endif

#endif //BOMBERMAN_SHARDE_H
