/*
** InterfaceGuest.c for Bomberman
** 
** Made by YOUBI David on 29/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 29 mai 13:00 2017 dyoubi
** Last update 29 mai 13:00 2017 dyoubi
*/

#include "InterfaceGuest.h"

SDL_Texture *g_in_lobby;
SDL_Texture *g_out_lobby;
SDL_Texture *g_ready;

int initGuestScreen() {
    TTF_Font *font;
    SDL_Surface *surface;
    static const SDL_Color White = {255, 255, 255};
    static const SDL_Color selectColor = {240, 180, 50};

    static const char inLobby[] = "Connecte";
    static const char outLobby[] = "Deconnecte";
    static const char ready[] = "Pret";

    font = TTF_OpenFont("ressources/fonts/upheavtt.ttf", 32);

    if (!font) {
        printf("Impossible d'ouvrir la police %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    surface = TTF_RenderText_Solid(font, inLobby, selectColor);
    g_in_lobby = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, outLobby, White);
    g_out_lobby = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, ready, selectColor);
    g_ready = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_FreeSurface(surface);

    TTF_CloseFont(font);
    return EXIT_SUCCESS;
}

t_menu *initGuestMenu() {
    t_menu *l_guestMenu;

    l_guestMenu = createMenu("Guest", GUEST_MENU_SIZE);

    if (l_guestMenu == NULL) {
        perror("Can't allocate memory\n");
        return (NULL);
    }

    if (!allocateMenuMemory(l_guestMenu, GUEST_MENU_SIZE)) {
        perror("Can't allocate memory\n");
        return (NULL);
    };

    l_guestMenu->ChoiceList[0] = ("choisir serveur");
    l_guestMenu->ChoiceList[1] = ("Se connecter");
    l_guestMenu->ChoiceList[2] = ("retour");

    int rc = createMenuItem(l_guestMenu, GUEST_MENU_SIZE);

    if (rc != EXIT_SUCCESS) {
        perror("Impossible de creer l'item %s");
    }

    l_guestMenu->actionList[0] = chooseServer;
    l_guestMenu->actionList[1] = connectToHost;
    l_guestMenu->actionList[2] = NULL;

    initGuestScreen();

    return l_guestMenu;
}

void drawGuestScreen() {
    SDL_Rect dest = {0, 0, 0, 0};
    static SDL_Texture *connected_texture;

    pthread_mutex_lock(&g_game.mutex);
    if (g_game.player_infos[0]->connected == 0x01) {
        connected_texture = g_in_lobby;
    } else if (g_game.player_infos[0]->connected == 0x00) {
        connected_texture = g_out_lobby;
    } else if (g_game.ready) {
        connected_texture = g_ready;
    }
    pthread_mutex_unlock(&g_game.mutex);

    SDL_QueryTexture(connected_texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = (WINDOWS_WIDTH / 2) - (dest.w / 2);
    dest.y = (WINDOWS_HEIGHT - dest.h);

    pthread_mutex_lock(&g_game.mutex);
    SDL_RenderCopy(g_game_engine.renderer, connected_texture, NULL, &dest);
    pthread_mutex_unlock(&g_game.mutex);

}