/*
** map.h for Bomberman
** 
** Made by YOUBI David on 06/06/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 06 juin 09:48 2017 dyoubi
** Last update 06 juin 09:48 2017 dyoubi
*/

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include "defs.h"
#include "sharde.h"
#include "structs.h"

t_map *chargerMap(const char *p_mapPath);

void chargerLevel(FILE *p_file, t_map *p_map);

void chargerTileSet(FILE *p_file, t_map *p_map);

int afficherMap(t_map *p_map, SDL_Surface *p_screen);

bool CollisionBox(t_map *p_map, SDL_Rect *p_player);

#endif //BOMBERMAN_MAP_H
