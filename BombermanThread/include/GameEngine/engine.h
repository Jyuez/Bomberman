/*
** engine.h for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 10:12 2017 dyoubi
** Last update 23 mai 10:12 2017 dyoubi
*/

#ifndef BOMBERMAN_ENGINE_H
#define BOMBERMAN_ENGINE_H

#include "structs.h"


int initEngine(t_game_engine *p_game_engine);

int cleanEngine(t_game_engine *p_game_engine);

SDL_Texture * TextureFromText(char *p_text, TTF_Font *p_font, SDL_Color p_color);
void drawInputText(char *p_input_text, int p_x, int p_y);
//void capFramerate();
//
//Uint32 timeLeft();

#endif //BOMBERMAN_ENGINE_H
