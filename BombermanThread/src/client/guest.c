/*
** guest.c for Bomberman
** 
** Made by YOUBI David on 29/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 29 mai 12:31 2017 dyoubi
** Last update 29 mai 12:31 2017 dyoubi
*/

#include <sharde.h>
#include <GameEngine/engine.h>
#include "guest.h"

int initGuest() {
    t_player_infos *new_player_infos;
    new_player_infos = calloc(1, sizeof(t_player_infos));

    new_player_infos->connected = 0x00;
    pthread_mutex_lock(&g_game.mutex);
    g_game.player_infos[0] = new_player_infos;
    pthread_mutex_unlock(&g_game.mutex);

    return EXIT_SUCCESS;
}

int guestLoop() {
    SDL_Event event;
    static t_menu *guestMenu = NULL;
    bool run;

    run = true;

    if (!guestMenu) {
        guestMenu = initGuestMenu();
        if (!guestMenu) {
            perror("Impossible de charger le menu... \n");
            return (EXIT_FAILURE);
        }
    }

    initNetwork();
    initGuest();
    guestMenu->showMenu = true;
    while (run) {
        pthread_mutex_lock(&g_game.mutex);
        SDL_RenderClear(g_game_engine.renderer);
        pthread_mutex_unlock(&g_game.mutex);

        run = EventHandlerClient(&event, guestMenu);

        drawMenu(guestMenu);
        drawInputText(g_game.ipHost, 10, 10);
        drawGuestScreen();

        pthread_mutex_lock(&g_game.mutex);
        SDL_RenderPresent(g_game_engine.renderer);
        pthread_mutex_unlock(&g_game.mutex);
    }

    return (EXIT_SUCCESS);
}