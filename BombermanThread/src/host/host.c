//
// Created by David on 26/05/2017.
//

#include "host.h"

int initHost() {
    pthread_mutex_lock(&g_game.mutex);
    g_game.my_infos->connected = 1;
    pthread_mutex_unlock(&g_game.mutex);

    return EXIT_SUCCESS;
}

void HostLoop() {
    SDL_Event event;
    bool run;
    static t_menu *HostMenu = NULL;
    run = true;

    if (!HostMenu) {
        HostMenu = initHostMenu();
        if (HostMenu == NULL) {
            perror("Impossible de charger le menu... \n");
            exit(EXIT_FAILURE);
        }
    }

    initNetwork();
    initHost();
    startupServer();
    HostMenu->showMenu = true;
    while (run) {
        pthread_mutex_lock(&g_game.mutex);
        SDL_RenderClear(g_game_engine.renderer);
        pthread_mutex_unlock(&g_game.mutex);

        run = EventHandlerHost(&event, HostMenu);

        drawMenu(HostMenu);

        pthread_mutex_lock(&g_game.mutex);
        ShowHostScreen();
        pthread_mutex_unlock(&g_game.mutex);

        pthread_mutex_lock(&g_game.mutex);
        SDL_RenderPresent(g_game_engine.renderer);
        pthread_mutex_unlock(&g_game.mutex);
    }
}

int openSlot(int *p_index) {
    int indexPlayer = (*p_index);

    if (dockClient(g_game.client_player[indexPlayer]) == EXIT_SUCCESS) {
        serverLoop(g_game.client_player[indexPlayer], g_game.player_infos[indexPlayer]);
        printf("Player connected on Port %d\n", PORT_1);
    } else perror("Error: client not connected");

    pthread_exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

