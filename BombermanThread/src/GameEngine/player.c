//
// Created by David on 28/05/2017.
//

#include "player.h"

void initPlayer(t_player_infos *p_player) {

    p_player->bombs_capacity = (20);
    p_player->bombs_left = (20);

    p_player->max_speed = (5);
    p_player->current_dir = (0);
    p_player->current_speed = (0);

    p_player->x_pos = (32);
    p_player->y_pos = (32);

    p_player->connected = 1;
    p_player->alive = 1;
    p_player->isReady = 0;
}
