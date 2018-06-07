/*
** ActionLauncher.c for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 11:03 2017 dyoubi
** Last update 23 mai 11:03 2017 dyoubi
*/

#include <host/InterfaceHost.h>
#include "ActionLauncher.h"
#include "network.h"
#include "server.h"
#include "host.h"
#include "guest.h"

void runHostMode() {
    SDL_SetRenderDrawColor(g_game_engine.renderer, 45, 78, 125, 255);
    HostLoop();
}

void runClientMode() {
    printf("client mode non implemente.\n");
    SDL_SetRenderDrawColor(g_game_engine.renderer, 78, 45, 125, 255);
    guestLoop();
}