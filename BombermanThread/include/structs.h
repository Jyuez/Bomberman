/*
** structs.h for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 09:59 2017 dyoubi
** Last update 23 mai 09:59 2017 dyoubi
*/

#ifndef BOMBERMAN_STRUCTS_H
#define BOMBERMAN_STRUCTS_H

#include "defs.h"

typedef char t_tile_index;

typedef struct s_tile {
    SDL_Rect rect;
    unsigned char plein;
    unsigned char etat;
    unsigned char type;
} t_tile;

typedef struct s_map {
    int sizeX;
    int sizeY;
    int nbLayer;
    int nbTilesX, nbTilesY;
    t_tile *props;
    t_tile_index **schema;
    SDL_Surface *tileset;
    SDL_Texture *texture;
} t_map;

typedef struct s_level {
    int nbMap;
    t_map **mapList;
} t_level;

typedef struct s_game_engine {
    SDL_Renderer *renderer;
    SDL_Window *window;
} t_game_engine;

typedef struct s_player_infos {
    char connected;
    char alive;
    char current_dir;
    char isReady;
    uint32_t x_pos;
    uint32_t y_pos;
    uint32_t current_speed;
    uint32_t max_speed;
    uint32_t bombs_left;
    uint32_t bombs_capacity;
    uint32_t frags;
} t_player_infos;

typedef struct s_client_player {
    struct sockaddr_in server_sin;
    struct sockaddr_in *client_sin;
    SOCKET client;
    SOCKET server;
    uint32_t size;
} t_client_player;

typedef struct s_client_request {
    unsigned int magic;
    int x_pos;
    int y_pos;
    int dir;
    int command;
    int speed;
    int ckecksum;
} t_client_request;

typedef struct s_game_mode {
    bool host;
    bool ready;
} t_game_mode;


typedef struct s_game {
    pthread_mutex_t mutex; //Protection des donnees (Host/Guest)

    struct s_player_infos *my_infos;
    struct s_player_infos *player_infos[MAX_PLAYER]; //Liste des joueurs de la partie, le joueur compris (Host/Guest)
    struct s_client_player *client_player[MAX_PLAYER - 1]; //Liste des client (Host)
    struct s_map *map; // (Host/Guest)
    SOCKET server; // (Host/Guest)
    struct sockaddr_in server_sin; // (Host/Guest)
    uint32_t portHost;
    char ipHost[512];
    bool inGame; //Si une partie est en cour (Host/Guest)
    bool host; //True si le joueur est l'host de la partie
    bool ready; //Le joueur est pret a joueur (Host/Guest)
    uint32_t numberInGame;
} t_game;

typedef struct s_menu {
    int currentSelected;        //Index vers le choix courrant
    int size;
    bool isCurrent;
    bool showMenu;              // Si le menu doit être affiche
    char *menuName;
    char **ChoiceList;
    SDL_Texture **texture_list;
    SDL_Texture **texture_selected;

    void (**actionList)(void);
} t_menu;


#endif //BOMBERMAN_STRUCTS_H
