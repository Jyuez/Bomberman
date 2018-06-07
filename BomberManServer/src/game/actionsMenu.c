//
// Created by David on 21/05/2017.
//

#include <network/server.h>
#include "actionsMenu.h"
#include "mainLoop.h"
#include "game/menuTree/menu.h"

void EnableServeur() {
    pthread_t *threadMatchmaking;
    static pthread_mutex_t mutex;
    mutex = PTHREAD_MUTEX_INITIALIZER;

    printf("Lancement du matchmaking\n");

    pthread_mutex_lock(&mutex);
    getGame()->threadMatchmaking = threadMatchmaking;
    pthread_mutex_unlock(&mutex);

    if (pthread_create(threadMatchmaking, PTHREAD_CREATE_JOINABLE, (void *) matchMaking, NULL))
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Impossible de creer le thread d'ecoute: %d\n", SDL_GetError());
    else printf("En attente de joueur...\n");
}

void EnableClient() {
    init();

}

void startParty() {

}

void closeParty() {
    quit(EXIT_SUCCESS);

}


void launcher() {

    static pthread_mutex_t mutex;
    mutex = PTHREAD_MUTEX_INITIALIZER;
    t_game *gameState;
    pthread_t *sniffer;

    pthread_mutex_lock(&mutex);
    gameState = getGame();
    pthread_mutex_unlock(&mutex);

    SDL_Log("Launcher...\n");
    if (gameState == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Impossible d'initialiser les donnees de la partie.\nExit\n");
        quit(EXIT_FAILURE);
    }

    if (gameState->isMatchmaking == false) {
        //TODO: Entrer dans l'ecran de matchmaking
        EnableServeur();
        printf("Le thread d'ecoute est lance\n");

    } else
        printf("Le matchmaking est deja en cours..\n");
}


void reachSubMenu() {
    t_menu *currentMenu = getCurrentMenu();
    int target = currentMenu->currentSelected;
    if (currentMenu->listItem[target]->subMenu) {
        currentMenu->showMenu = false;
        currentMenu->isCurrent = false;

        setCurrentMenu(currentMenu->listItem[target]->subMenu);

        getCurrentMenu()->currentSelected = 0;
        getCurrentMenu()->showMenu = true;
        getCurrentMenu()->isCurrent = true;
    } else
        SDL_Log("No submenu to reach\n");

}

void reachParentMenu() {
    t_menu *currentMenu = getCurrentMenu();
    if (currentMenu->parentMenu) {
        currentMenu->showMenu = false;
        currentMenu->isCurrent = false;

        setCurrentMenu(currentMenu->parentMenu);

        getCurrentMenu()->currentSelected = 0;
        getCurrentMenu()->showMenu = true;
        getCurrentMenu()->isCurrent = true;
    } else
        SDL_Log("No parent menu to reach\n");

}

void endGame() {
    quit(EXIT_SUCCESS);
}