//
// Created by David on 21/05/2017.
//
#include "network.h"

void init(void) {
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