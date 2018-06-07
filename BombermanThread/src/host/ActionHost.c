//
// Created by David on 26/05/2017.
//

#include <defs.h>
#include "ActionHost.h"

void addPlayer() {
    pthread_t threadMatchmaking;
    pthread_attr_t threadAttributes;
    int ret;
    static int indexPlayer = 1;
    int indexPlayerTmp;

    ret = pthread_attr_init(&threadAttributes);
    ret = pthread_attr_setdetachstate(&threadAttributes, PTHREAD_CREATE_JOINABLE);

    if (indexPlayer < MAX_PLAYER - 1) {
        indexPlayerTmp = indexPlayer;
        printf("Openning slot: %d\n", indexPlayer);
        if (pthread_create(&threadMatchmaking, &threadAttributes, (void *) openSlot, &indexPlayerTmp))
            perror("Impossible de creer le thread d'ecoute");
        indexPlayer++;
    } else {
        printf("All slot are taken\n");
    }
}

void startGame() {
    static pthread_t threadGame;
    static pthread_attr_t threadAttributes;

    /* TODO: Lancement d'une partie
     * 1 - Charger et construire la carte
     * 2 - Positionner les joueurs
     * 3 - Attendre que tout les client soit prêt a jouer
     * 4 - Lancer le thread de jeu
     */

    // 1 - Charger et construire la carte

    if (!g_game.ready) {
        pthread_mutex_lock(&g_game.mutex);

        g_game.map = chargerMap("ressources/maps/map0.txt");
        SDL_Log("La carte est chargée avec succes");
        //2 - Positionner les joueurs sur la carte
        g_game.my_infos->x_pos = 32;
        g_game.my_infos->y_pos = 32;
        g_game.my_infos->isReady = 1;
        g_game.ready = true;

        pthread_mutex_unlock(&g_game.mutex);
    }

    if (g_game.numberInGame > 1) {
        //3 - Attendre que tout les clients soit prêt a jouer
        for (int index = 1; index < g_game.numberInGame; ++index) {
            if (!g_game.player_infos[index]->isReady) {
                g_game.ready = false;
                SDL_Log("Waiting player: %d", index);
            }
        }
    }
    printf("running game comming soon...\n");
}