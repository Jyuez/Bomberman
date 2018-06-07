/*
** client.c for Bomberman
** 
** Made by YOUBI David on 30/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 30 mai 09:37 2017 dyoubi
** Last update 30 mai 09:37 2017 dyoubi
*/

#include <structs.h>
#include <sharde.h>
#include <GameEngine/player.h>
#include <pthread_time.h>
#include <fcntl.h>
#include "network.h"
#include "client.h"

/*La fonction connecToHost permet essai de se connecter sur les ports connu.
 * Si la connection echoue sur tout les port renvoie EXIT_FAILURE si non retourne le nouveau socket*/
SOCKET tryHost(const char *p_ip) {
    SOCKET sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        perror("Impossible de creer le socket de connection au serveur\n");
        return EXIT_FAILURE;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(p_ip);
    serv_addr.sin_port = htons(PORT_1);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != SOCKET_ERROR) {
        return sockfd;
    }

    perror("Impossible de se connecter au serveur");
    return EXIT_FAILURE;
}

t_player_infos *confirmConnection(SOCKET sockfd) {
    char connected;
    int result;
    t_player_infos *playerBuffer;
    t_player_infos *playerinfos;
    connected = 1;

    playerBuffer = calloc(1, sizeof(t_player_infos));

    result = recv(sockfd, (char *) playerBuffer, sizeof(t_player_infos), 0);
    printf("rcv result: %d\n", result);

    result = send(sockfd, &connected, sizeof(char), 0);
    printf("send result: %d\n", result);


    playerinfos = getReadbleInfos(playerBuffer);
    free(playerBuffer);

    return playerinfos;
}