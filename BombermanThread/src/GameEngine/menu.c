//
// Created by David on 26/05/2017.
//

#include "menu.h"

///createMenu - Cette methode permet de creer un menu
///@param p_itemList - Tableau de chaine de caractère les entree du menu
///@param p_listSize - Taille de la liste
///@param p_menuName - Nom du menu
t_menu *createMenu(char *p_menuName, int p_listSize) {

    t_menu *menu;
    menu = malloc(sizeof(t_menu));

    if (menu == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Impossible de creer le menu %s\n", p_menuName);
        return NULL;
    }

    menu->currentSelected = 0;
    menu->menuName = strdup(p_menuName);

    /*Par defaut, le menu est caché*/
    menu->showMenu = false;
    menu->isCurrent = false;
    menu->size = p_listSize;

    return menu;
}

int createMenuItem(t_menu *p_menu, int p_menuSize) {

    SDL_Color White = {255, 255, 255};
    SDL_Color selectColor = {240, 180, 50};
    TTF_Font *font;

    font = TTF_OpenFont("ressources/fonts/upheavtt.ttf", 32);

    if (!font) {
        perror("Impossible d'ouvrir la police\n");
        return EXIT_FAILURE;
    }

    for (int index = 0; index < p_menuSize; ++index) {
        p_menu->texture_list[index] = SDL_CreateTextureFromSurface(g_game_engine.renderer,
                                                                   TTF_RenderText_Solid(font, p_menu->ChoiceList[index],
                                                                                        White));
        p_menu->texture_selected[index] = SDL_CreateTextureFromSurface(g_game_engine.renderer,
                                                                       TTF_RenderText_Solid(font,
                                                                                            p_menu->ChoiceList[index],
                                                                                            selectColor));
        if (p_menu->texture_list[index] == NULL || p_menu->texture_selected[index] == NULL) {
            perror("Impossible de creer la texture demandee.\n");
            return EXIT_FAILURE;
        }
    }

    TTF_CloseFont(font);
    return EXIT_SUCCESS;

}

void drawMenu(t_menu *p_menu) {
    SDL_Rect dest = {0, 0, 0, 0};
    SDL_Rect previousDest = {0, WINDOWS_HEIGHT / 3, 0, 0};
    int interval = 8;

    pthread_mutex_lock(&g_game.mutex);

    if (p_menu->showMenu) {
        for (int index = 0; index < p_menu->size; ++index) {
            if (p_menu->texture_list[index] != NULL) {

                SDL_QueryTexture(p_menu->texture_list[index], NULL, NULL, &dest.w, &dest.h);
                dest.x = (WINDOWS_WIDTH / 2) - (dest.w / 2);
                dest.y = previousDest.y + previousDest.h + interval;

                if (p_menu->currentSelected == index) {
                    SDL_RenderCopy(g_game_engine.renderer, p_menu->texture_selected[index], NULL, &dest);

                } else {
                    SDL_RenderCopy(g_game_engine.renderer, p_menu->texture_list[index], NULL, &dest);
                }
                previousDest = dest;
            }
        }
    }

    pthread_mutex_unlock(&g_game.mutex);
}

bool allocateMenuMemory(t_menu *p_menu, int p_menuSize) {

    p_menu->actionList = malloc(sizeof(void *) * p_menuSize);

    if (p_menu->actionList == NULL) {
        perror("Can't allocate memory\n");
        return (false);
    }

    p_menu->ChoiceList = malloc(sizeof(char *) * p_menuSize);
    p_menu->texture_list = malloc(sizeof(SDL_Texture *) * p_menuSize);
    p_menu->texture_selected = malloc(sizeof(SDL_Texture *) * p_menuSize);

    if (p_menu->ChoiceList == NULL
        || p_menu->texture_list == NULL
        || p_menu->texture_selected == NULL) {
        perror("Can't allocate memory\n");
        return (false);
    }
    return (true);
}

void clearMenu(t_menu *p_menu) {

    for (int index = 0; index < p_menu->size; ++index) {
        if (p_menu->ChoiceList[index])
            free(p_menu->ChoiceList[index]);
        if (p_menu->actionList[index])
            free(p_menu->actionList[index]);
        SDL_DestroyTexture(p_menu->texture_selected[index]);
        SDL_DestroyTexture(p_menu->texture_list[index]);
    }
}