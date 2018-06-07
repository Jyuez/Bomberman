//
// Created by David on 21/05/2017.
//

#include "game/menuTree/menu.h"

///createMenu - Cette methode permet de creer un menu
///@param p_itemList - Tableau de chaine de caractère les entree du menu
///@param p_listSize - Taille de la liste
///@param p_menuName - Nom du menu
t_menu *createMenu(char *p_menuName, int p_listSize, t_menu *p_parentMenu) {

    t_menu *l_newMenu;

    l_newMenu = malloc(sizeof(t_menu));
    if (l_newMenu == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Impossible de creer le menu %s\n", p_menuName);
        return NULL;
    }
    l_newMenu->currentSelected = 0;
    l_newMenu->menuName = strdup(p_menuName);
    l_newMenu->parentMenu = p_parentMenu;

    /*Par defaut, le menu est caché*/
    l_newMenu->showMenu = false;
    l_newMenu->isCurrent = false;
    l_newMenu->size = p_listSize;
    if (p_listSize > 0) {
        l_newMenu->listItem = malloc(sizeof(t_menu_item) * p_listSize + 1);

    } else l_newMenu->listItem[p_listSize] = NULL;
    return l_newMenu;
}

///createMenuItem
///@param p_itemName - Nom de l'item a creer
///@param p_action - pointeur vers l'action activable, NULL si aucune action
t_menu_item *createMenuItem(char *p_itemName, void *p_action, t_menu *p_subMenu) {
    SDL_Color colorSelect = {125, 255, 255};
    t_menu_item *l_newItem = malloc(sizeof(t_menu_item));


    SDL_Color White = {255, 255, 255};
    SDL_Color selectColor = {240, 180, 50};
    TTF_Font *font = TTF_OpenFont("ressources/fonts/upheavtt.ttf", 32);

    if (l_newItem == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Impossible de creer l'item %s", p_itemName);
        return NULL;
    }
    l_newItem->action = p_action;
    l_newItem->itemName = strdup(p_itemName);
    l_newItem->isSelected = false;
    if (p_subMenu) l_newItem->subMenu = p_subMenu;
    else l_newItem->subMenu = NULL;


    l_newItem->text = SDL_CreateTextureFromSurface(getRenderer(), TTF_RenderText_Solid(font, p_itemName, White));
    l_newItem->textSelected = SDL_CreateTextureFromSurface(getRenderer(),
                                                           TTF_RenderText_Solid(font, p_itemName, selectColor));

    if ((l_newItem->text == NULL) || (l_newItem->textSelected == NULL)) {
        return NULL;
    }
    TTF_CloseFont(font);

    return l_newItem;
}

void initMainMenu() {
    t_menu *g_mainMenu;
    t_menu *g_hostMenu;
    t_menu *g_clientMenu;
    t_menu *g_exitMenu;

    void **g_mainMenuActions = malloc(sizeof(void *) * (MAIN_MENU_SIZE + 1));
    void **g_hostActions = malloc(sizeof(void *) * (HOST_MENU_SIZE + 1));
    void **g_clientActions = malloc(sizeof(void *) * (HOST_MENU_SIZE + 1));
    void **g_exitAction = malloc(sizeof(void *) * 3);


    char **g_mainMenuSubitem = malloc(sizeof(char) * 256 * (MAIN_MENU_SIZE + 1));
    char **g_hostSubitem = malloc(sizeof(char) * 256 * (HOST_MENU_SIZE + 1));
    char **g_clientSubitem = malloc(sizeof(char) * 256 * (CLIENT_MENU_SIZE + 1));
    char **g_exitSubitem = malloc(sizeof(char) * 256 * 3);

    t_menu **g_mainMenuSubmenu = malloc(sizeof(t_menu *) * (MAIN_MENU_SIZE + 1));
    t_menu **g_hostMenuSubmenu = malloc(sizeof(t_menu *) * (MAIN_MENU_SIZE + 1));
    t_menu **g_clientMenuSubmenu = malloc(sizeof(t_menu *) * (MAIN_MENU_SIZE + 1));
    t_menu **g_extiSubmenu = malloc(sizeof(t_menu *) * 3);

    g_mainMenu = createMenu("menu principal", MAIN_MENU_SIZE, NULL);
    if (g_mainMenu == NULL) {
        exit(EXIT_FAILURE);
    }

    g_hostMenu = createMenu("menu host", HOST_MENU_SIZE, g_mainMenu);
    if (g_hostMenu == NULL) {
        exit(EXIT_FAILURE);
    }

    g_clientMenu = createMenu("menu client", CLIENT_MENU_SIZE, g_mainMenu);
    if (g_clientMenu == NULL) {
        exit(EXIT_FAILURE);
    }

    g_exitMenu = createMenu("quitter", 2, g_mainMenu);
    if (g_exitMenu == NULL) {
        exit(EXIT_FAILURE);
    }

    g_mainMenuActions[0] = reachSubMenu;
    g_mainMenuActions[1] = reachSubMenu;
    g_mainMenuActions[2] = reachSubMenu;
    g_hostActions[0] = launcher;
    g_hostActions[1] = reachParentMenu;
    g_clientActions[0] = NULL;
    g_clientActions[1] = NULL;
    g_clientActions[2] = reachParentMenu;
    g_exitAction[0] = reachParentMenu;
    g_exitAction[1] = endGame;

    g_mainMenuSubitem[0] = strdup("Heberger une partie");
    g_mainMenuSubitem[1] = strdup("Multijoueur");
    g_mainMenuSubitem[2] = strdup("Quitter");
    g_hostSubitem[0] = strdup("Lancer matchmaking");
    g_hostSubitem[1] = strdup("Retour");
    g_clientSubitem[0] = strdup("Options de connexion");
    g_clientSubitem[1] = strdup("Rejoindre");
    g_clientSubitem[2] = strdup("retour");
    g_exitSubitem[0] = strdup("Annuler");
    g_exitSubitem[1] = strdup("Confirmer");

    g_mainMenuSubmenu[0] = g_hostMenu;
    g_mainMenuSubmenu[1] = g_clientMenu;
    g_mainMenuSubmenu[2] = g_exitMenu;

    g_hostMenuSubmenu[0] = NULL;
    g_hostMenuSubmenu[1] = NULL;

    g_clientMenuSubmenu[0] = NULL;
    g_clientMenuSubmenu[1] = NULL;
    g_clientMenuSubmenu[2] = NULL;

    g_extiSubmenu[0] = NULL;
    g_extiSubmenu[1] = NULL;

    for (int index = 0; index < g_mainMenu->size; ++index) {
        g_mainMenu->listItem[index] = createMenuItem(g_mainMenuSubitem[index], g_mainMenuActions[index],
                                                     g_mainMenuSubmenu[index]);
    }
    g_mainMenu->listItem[g_mainMenu->size + 1] = NULL;

    //---
    for (int index = 0; index < g_hostMenu->size; ++index) {
        g_hostMenu->listItem[index] = createMenuItem(g_hostSubitem[index], g_hostActions[index],
                                                     g_hostMenuSubmenu[index]);
    }
    g_hostMenu->listItem[g_hostMenu->size + 1] = NULL;


    for (int index = 0; index < g_clientMenu->size; ++index) {
        g_clientMenu->listItem[index] = createMenuItem(g_clientSubitem[index], g_clientActions[index],
                                                       g_clientMenuSubmenu[index]);
    }
    g_clientMenu->listItem[g_clientMenu->size + 1] = NULL;


    for (int index = 0; index < g_exitMenu->size; ++index) {
        g_exitMenu->listItem[index] = createMenuItem(g_exitSubitem[index], g_exitAction[index], g_extiSubmenu[index]);
    }
    g_exitMenu->listItem[g_exitMenu->size + 1] = NULL;
    //---
    setCurrentMenu(g_mainMenu);
}

void drawMenu(t_menu *p_menu) {
    SDL_Rect dest = {0, 0, 0, 0};
    SDL_Rect previousDest = {0, WINDOWS_HEIGHT / 3, 0, 0};
    int interval = 8;
    SDL_Renderer *renderer = getRenderer();

    if (p_menu->showMenu) {
        for (int index = 0; index < p_menu->size; ++index) {
            if (p_menu->listItem[index] != NULL) {
                SDL_QueryTexture(p_menu->listItem[index]->text, NULL, NULL, &dest.w, &dest.h);
                dest.x = (WINDOWS_WIDTH / 2) - (dest.w / 2);
                dest.y = previousDest.y + previousDest.h + interval;

                if (p_menu->listItem[index]->isSelected) {
                    SDL_RenderCopy(renderer, p_menu->listItem[index]->textSelected, NULL, &dest);
                } else {
                    SDL_RenderCopy(renderer, p_menu->listItem[index]->text, NULL, &dest);
                }
                previousDest = dest;
            }
        }
    }

    //TODO: Construire et afficher le menuScreen
}