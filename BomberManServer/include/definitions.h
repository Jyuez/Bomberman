//
// Created by David on 21/05/2017.
//

#ifndef BOMBERCLIENT_DEFINITIONS_H
#define BOMBERCLIENT_DEFINITIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define BASE_PATH_TILE      "ressources/tileset/"
#define BASE_PATH_SPRITES   "ressources/sprite/"
#define BASE_PATH_MAP       "ressources/map/"
#define BASE_PATH_FONT      "ressources/fonts/"

#define WINDOWS_WIDTH           800
#define WINDOWS_HEIGHT          480
#define TIME_BETWEEN_2_FRAMES   20
#define TICK_INTERVAL           10

#define MAX_PLAYER              4
#define PORT_1                  7450
#define PORT_2                  7451
#define PORT_3                  7452

#define COMMON_MIN(a, b) (((a)<(b))?(a):(b))
#define COMMON_MAX(a, b) (((a)>(b))?(a):(b))

#define MAIN_MENU_SIZE 3
#define HOST_MENU_SIZE 2
#define CLIENT_MENU_SIZE 3

#endif //BOMBERCLIENT_DEFINITIONS_H
