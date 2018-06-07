//
// Created by David on 15/06/2017.
//

#include "lobby/InterfaceLobby.h"

t_menu *initLobbyMenu() {
    t_menu *menu = NULL;

    menu = createMenu("lobby", 2);

    if (menu == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory\n");
        perror("Impossible d'initialiser le lobby");
        return NULL;
    }

    if (!allocateMenuMemory(menu, 2)) {
        perror("Impossible d'initialiser le lobby");
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory\n");
        return (NULL);
    };

    /*Les nom des choix du menu*/
    l_mainMenu->ChoiceList[0] = ("prêt");
    l_mainMenu->ChoiceList[1] = ("quitter");

    int rc = createMenuItem(menu, 2);

    if (rc != EXIT_SUCCESS) {
        perror("Impossible d'initialiser le lobby");
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Impossible de creer l'item %s", SDL_GetError());
        return NULL;
    }

    l_mainMenu->actionList[0] = NULL;
    l_mainMenu->actionList[1] = NULL;

    printf("Menu charge avec succes\n");
    return menu;
}