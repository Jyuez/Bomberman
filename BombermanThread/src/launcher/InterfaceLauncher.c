/*
** InterfaceLauncher.c for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 10:52 2017 dyoubi
** Last update 23 mai 10:52 2017 dyoubi
*/

#include "InterfaceLauncher.h"
#include "ActionLauncher.h"

t_menu *initLauncherMenu() {
    t_menu *l_mainMenu;
    printf("Chargement du menu\n");

    l_mainMenu = createMenu("menu principal", MAIN_MENU_SIZE);

    if (l_mainMenu == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory\n");
        return (NULL);
    }

    if (!allocateMenuMemory(l_mainMenu, MAIN_MENU_SIZE)) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Can't allocate memory\n");
        return (NULL);
    };


    /*Les nom des choix du menu*/
    l_mainMenu->ChoiceList[0] = ("Heberger une partie");
    l_mainMenu->ChoiceList[1] = ("Chercher une partie");
    l_mainMenu->ChoiceList[2] = ("Quitter");


    int rc = createMenuItem(l_mainMenu, MAIN_MENU_SIZE);

    if (rc != EXIT_SUCCESS) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Impossible de creer l'item %s", SDL_GetError());
    }


    /*Les actions cu menu possiblz*/
    l_mainMenu->actionList[0] = runHostMode;
    l_mainMenu->actionList[1] = runClientMode;
    l_mainMenu->actionList[2] = NULL;

    printf("Menu charge avec succes\n");
    return l_mainMenu;
}