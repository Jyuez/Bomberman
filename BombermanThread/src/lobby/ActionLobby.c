//
// Created by David on 15/06/2017.
//

#include "ActionLobby.h"
#include "EventLobby.h"
#include "InterfaceLobby.h"

void readToPlay(){
    pthread_mutex_lock(&g_game.mutex);
    g_game.my_infos->isReady = 1;
    pthread_mutex_unlock(&g_game.mutex);
}