/*
** defs.h for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 09:55 2017 dyoubi
** Last update 23 mai 09:55 2017 dyoubi
*/

#ifndef BOMBERMAN_DEFS_H
#define BOMBERMAN_DEFS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifdef WIN32

#include <winsock2.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#define BASE_PATH_TILE      "ressources/tileset/"
#define BASE_PATH_SPRITES   "ressources/sprite/"
#define BASE_PATH_MAP       "ressources/map/"
#define BASE_PATH_FONT      "ressources/fonts/"

#define WINDOWS_WIDTH           800
#define WINDOWS_HEIGHT          480
#define TILE_WIDTH              32
#define TILE_HEIGHT             32
#define TILE_NUMBER_X           25
#define TILE_NUMBER_Y           15

#define TIME_BETWEEN_2_FRAMES   20
#define TICK_INTERVAL           10

#define MAX_PLAYER              4
#define PORT_1                  7450
#define PORT_2                  7451
#define PORT_3                  7452

#define COMMON_MIN(a, b) (((a)<(b))?(a):(b))
#define COMMON_MAX(a, b) (((a)>(b))?(a):(b))

#define MAIN_MENU_SIZE 3
#define HOST_MENU_SIZE 3
#define GUEST_MENU_SIZE 3

#endif //BOMBERMAN_DEFS_H
