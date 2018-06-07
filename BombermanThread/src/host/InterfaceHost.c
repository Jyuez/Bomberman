//
// Created by David on 26/05/2017.
//

#include <host/ActionHost.h>
#include "InterfaceHost.h"

SDL_Texture *g_connected;
SDL_Texture *g_desconnecter;

SDL_Texture *g_openSlot;

int initHostScreen() {
    TTF_Font *font;
    SDL_Surface *surface;

    static const SDL_Color White = {255, 255, 255};
    static const SDL_Color selectColor = {240, 180, 50};

    static const char connect[] = "Connecte";
    static const char desconnect[] = "Attente";
    static const char openSlot[] = "vide";

    font = TTF_OpenFont("ressources/fonts/upheavtt.ttf", 32);

    if (!font) {
        printf("Impossible d'ouvrir la police %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    surface = TTF_RenderText_Solid(font, connect, selectColor);
    g_connected = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, desconnect, White);
    g_desconnecter = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, openSlot, White);
    g_openSlot = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_FreeSurface(surface);

    TTF_CloseFont(font);
    return EXIT_SUCCESS;
}

t_menu *initHostMenu() {
    t_menu *l_hostMenu;

    printf("Chargement du menu\n");

    l_hostMenu = createMenu("Hebergeur", HOST_MENU_SIZE);

    if (l_hostMenu == NULL) {
        perror("Can't allocate memory\n");
        return (NULL);
    }

    if (!allocateMenuMemory(l_hostMenu, HOST_MENU_SIZE)) {
        perror("Can't allocate memory\n");
        return (NULL);
    };

    l_hostMenu->ChoiceList[0] = ("Lancer la partie");
    l_hostMenu->ChoiceList[1] = ("Ajouter un joueur");
    l_hostMenu->ChoiceList[2] = ("retour");

    int rc = createMenuItem(l_hostMenu, HOST_MENU_SIZE);

    if (rc != EXIT_SUCCESS) {
        perror("Impossible de creer l'item %s");
    }

    l_hostMenu->actionList[0] = startGame;
    l_hostMenu->actionList[1] = addPlayer;
    l_hostMenu->actionList[2] = NULL;

    initHostScreen();

    return l_hostMenu;
}

void drawScreen(SDL_Texture **p_textureList) {

    SDL_Rect dest = {0, 0, 0, 0};
    SDL_Rect previousDest = {0, 0, 0, 0};
    int interval = 30;

    for (int index = 0; index < MAX_PLAYER; ++index) {

        SDL_QueryTexture(p_textureList[index], NULL, NULL, &dest.w, &dest.h);

        dest.x = previousDest.x + previousDest.w + interval;
        dest.y = (WINDOWS_HEIGHT - 25);

        SDL_RenderCopy(g_game_engine.renderer, p_textureList[index], NULL, &dest);

        previousDest = dest;
    }
}

int ShowHostScreen() {
    SDL_Texture *connected_texture[MAX_PLAYER];

    for (int index = 0; index < MAX_PLAYER; ++index) {
        if (g_game.player_infos[index] != NULL && g_game.player_infos[index]->connected == 1) {
            connected_texture[index] = g_connected;
        } else {
            connected_texture[index] = g_desconnecter;
        }
//        printf("[DEBUG]%c, %c, : %c\n", 0,1, g_game.player_infos[index]->connected);
    }

    drawScreen(connected_texture);
    return EXIT_SUCCESS;
}