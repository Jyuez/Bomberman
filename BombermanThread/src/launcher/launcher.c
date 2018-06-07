/*
** launcher.c for Bomberman
**
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 09:52 2017 dyoubi
** Last update 23 mai 09:52 2017 dyoubi
*/

#include "launcher.h"
#include "InterfaceLauncher.h"

#include "defs.h"
#include "structs.h"
#include "sharde.h"
#include "EventLauncher.h"

int launcher() {
    SDL_Event event;
    bool run;
    t_menu *launcherMenu = NULL;

    launcherMenu = initLauncherMenu();

    if (!launcherMenu) {
        exit(EXIT_FAILURE);
    }

    run = true;
    launcherMenu->showMenu = true;
    while (run) {
        pthread_mutex_lock(&g_game.mutex);
        SDL_RenderClear(g_game_engine.renderer);
        pthread_mutex_unlock(&g_game.mutex);

        run = EventHandlerLauncher(&event, launcherMenu);

        drawMenu(launcherMenu);

        SDL_RenderPresent(g_game_engine.renderer);
    }

    return (EXIT_SUCCESS);
};
