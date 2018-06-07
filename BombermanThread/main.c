#define MAIN_FILE

#include <stdio.h>
#include <launcher/launcher.h>
#include "engine.h"
#include "sharde.h"

int main(int argc, char *argv[]) {

    if (initEngine(&g_game_engine) == EXIT_SUCCESS) {
        printf("Hello, World!\n");
    };


    if (pthread_mutex_init(&g_game.mutex, NULL) != 0) {
        perror("Impossible d'initialiser le mutex\n Erreur critique. Exit\n");
        return EXIT_FAILURE;
    };

    g_game.numberInGame = 0;
    for (int index = 0; index < MAX_PLAYER; ++index) {
        g_game.player_infos[index] = calloc(1, sizeof(t_player_infos));
    }

    for (int index = 0; index < MAX_PLAYER; ++index) {
        g_game.client_player[index] = calloc(1, sizeof(t_client_player));
    }

    g_game.my_infos = g_game.player_infos[0];
    g_game.numberInGame++;

    SDL_SetRenderDrawColor(g_game_engine.renderer, 124, 22, 54, 255);
    g_game.portHost = PORT_1;
    strcat(g_game.ipHost, "127.0.0.1");
    g_game.ready = false;
    g_game.inGame = false;
    g_game.host = false;

    launcher();

    if (cleanEngine(&g_game_engine) == EXIT_SUCCESS) {
        printf("Bye, World!\n");
    };

    return EXIT_SUCCESS;
}