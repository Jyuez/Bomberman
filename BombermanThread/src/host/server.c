//
// Created by David on 23/05/2017.
//

#include <structs.h>
#include <sharde.h>
#include <GameEngine/player.h>
#include "network.h"
#include "host/server.h"

int startupServer() {
    pthread_mutex_lock(&g_game.mutex);

    g_game.server_sin.sin_family = AF_INET;
    g_game.server_sin.sin_port = htons((u_short) PORT_1);
    g_game.server_sin.sin_addr.s_addr = INADDR_ANY;

    if ((g_game.server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        pthread_mutex_unlock(&g_game.mutex);
        perror("Impossible de creer le serveur");
        return EXIT_FAILURE;
    };

    if ((bind(g_game.server, (struct sockaddr *) &g_game.server_sin, sizeof(struct sockaddr_in))) < 0) {
        pthread_mutex_unlock(&g_game.mutex);
        perror("[ERROR]Impossbile de bind le server");
        return (EXIT_FAILURE);
    }
    pthread_mutex_unlock(&g_game.mutex);
    printf("Le serveur est pret\n");
    return EXIT_SUCCESS;
}

int dockClient(t_client_player *p_client_player) {
    int size;
    SOCKET sockClient;
    SOCKET sockServer;
    struct sockaddr_in *sin;

    size = sizeof(struct sockaddr_in);

    printf("Waiting ...\n");
    pthread_mutex_lock(&g_game.mutex);
    sockServer = g_game.server;
    pthread_mutex_unlock(&g_game.mutex);

    sin = calloc(1, sizeof(size));

    sockClient = (SOCKET) listen(sockServer, 0);

    if ((sockClient = accept(sockServer, (struct sockaddr *) sin, &size)) == INVALID_SOCKET) {
        printf("[ERROR]Can't accept client\n");
        return (EXIT_FAILURE);
    }

    printf("New client: %d\n", (int) sockClient);

    pthread_mutex_lock(&g_game.mutex);
    p_client_player->client = sockClient;
    p_client_player->client_sin = sin;
    pthread_mutex_unlock(&g_game.mutex);
    return (EXIT_SUCCESS);
}

bool initClient(t_client_player *p_client, t_player_infos *p_player_infos) {
    t_player_infos *sendableInfos;
    SOCKET client;
    bool result;
    result = false;

    pthread_mutex_lock(&g_game.mutex);
    initPlayer(p_player_infos);
    sendableInfos = (getSendableInfos(p_player_infos));
    client = p_client->client;
    pthread_mutex_unlock(&g_game.mutex);

    send(client, (char *) sendableInfos, sizeof(t_player_infos), 0);

    recv(client, &sendableInfos->connected, sizeof(char), 0);
    
    if (sendableInfos->connected == 1)
        result = true;

    pthread_mutex_lock(&g_game.mutex);
    p_player_infos->connected = sendableInfos->connected;
    pthread_mutex_unlock(&g_game.mutex);

    printf("[DEBUG]Connection result: %c, %c. --(player adress: %p)--\n", p_player_infos->connected,
           sendableInfos->connected,
           &p_player_infos);

    free(sendableInfos);
    return (result);
}

void serverLoop(t_client_player *p_client, t_player_infos *p_player_infos) {
    initClient(p_client, p_player_infos);
    if (p_player_infos->connected == 1) {
        pthread_mutex_lock(&g_game.mutex);
        g_game.numberInGame++;
        pthread_mutex_unlock(&g_game.mutex);
        printf("New player init success. Start communication...\n");
        //TODO: communiquer avec le client;
    }
}