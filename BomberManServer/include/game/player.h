//
// Created by David on 21/05/2017.
//

#ifndef BOMBERCLIENT_PLAYER_H
#define BOMBERCLIENT_PLAYER_H

#include "globals.h"

typedef struct s_player_infos
{
    char  connected;
    char  alive;
    int   x_pos;
    int   y_pos;
    int   current_dir;
    int   current_speed;
    int   max_speed;
    int   bombs_left;
    int   bombs_capacity;
    int   frags;
    int   socket;
} t_player_infos;

#endif //BOMBERCLIENT_PLAYER_H
