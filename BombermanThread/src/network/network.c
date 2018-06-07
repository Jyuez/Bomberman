//
// Created by David on 23/05/2017.
//

#include <structs.h>
#include "network/network.h"

void initNetwork(void) {
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (err < 0) {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
    SDL_Log("WSAStartup succes\n");
#endif
}

void end(void) {
#ifdef WIN32
    WSACleanup();
    SDL_Log("WSACLeanup\n");
#endif
}

t_player_infos *getSendableInfos(t_player_infos *p_player_infos) {
    t_player_infos *sendable;

    sendable = calloc(1, sizeof(t_player_infos));
    if (sendable) {
        sendable->x_pos = htonl(p_player_infos->x_pos);
        sendable->y_pos = htonl(p_player_infos->y_pos);

        sendable->current_speed = htonl(p_player_infos->current_speed);
        sendable->max_speed = htonl(p_player_infos->max_speed);

        sendable->bombs_left = htonl(p_player_infos->bombs_left);
        sendable->bombs_capacity = htonl(p_player_infos->bombs_capacity);

        sendable->frags = htonl(p_player_infos->frags);

        sendable->connected = p_player_infos->connected;
        sendable->current_dir = p_player_infos->current_dir;
        sendable->alive = p_player_infos->alive;
    }

    return sendable;
}

t_player_infos *getReadbleInfos(t_player_infos *p_player_infos) {
    t_player_infos *readble;

    readble = calloc(1, sizeof(t_player_infos));
    if (readble) {
        readble->x_pos = ntohl(p_player_infos->x_pos);
        readble->y_pos = ntohl(p_player_infos->y_pos);

        readble->current_speed = ntohl(p_player_infos->current_speed);
        readble->max_speed = ntohl(p_player_infos->max_speed);

        readble->bombs_left = ntohl(p_player_infos->bombs_left);
        readble->bombs_capacity = ntohl(p_player_infos->bombs_capacity);

        readble->frags = ntohl(p_player_infos->frags);

        readble->connected = p_player_infos->connected;
        readble->current_dir = p_player_infos->current_dir;
        readble->alive = p_player_infos->alive;
    }
    return readble;
}