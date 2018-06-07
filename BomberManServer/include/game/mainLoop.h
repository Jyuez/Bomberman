//
// Created by David on 21/05/2017.
//

#ifndef BOMBERCLIENT_MAINLOPP_H
#define BOMBERCLIENT_MAINLOPP_H

#include "globals.h"
#include "EventHandler.h"
#include "player.h"

typedef struct s_game {
    bool inParty;
    int nbConnected;
    //t_map map;
    bool isMatchmaking;
    pthread_t *threadMatchmaking;
    t_player_infos player_infos[MAX_PLAYER];
}t_game ;

void runGame();

#endif //BOMBERCLIENT_MAINLOPP_H
