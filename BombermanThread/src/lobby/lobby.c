//
// Created by David on 15/06/2017.
//

#include "lobby.h"
#include "InterfaceLobby.h"
#include "EventLobby.h"

int lobby() {
    SDL_Event event;
    bool run;
    t_menu *menu = NULL;
    menu = initLobbyMenu();

    if (!menu) {
        exit(EXIT_FAILURE);
    }

    run = true;
    menu->showMenu = true;

    while (run) {
        pthread_mutex_lock(&g_game.mutex);

        SDL_RenderClear(g_game_engine.renderer);
        run = EventHandlerLobby(&event, menu);
        SDL_RenderPresent(g_game_engine.renderer);

        pthread_mutex_unlock(&g_game.mutex);
    }
    return (EXIT_SUCCESS);
}