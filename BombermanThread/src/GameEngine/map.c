/*
** map.c for Bomberman
** 
** Made by YOUBI David on 06/06/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 06 juin 09:48 2017 dyoubi
** Last update 06 juin 09:48 2017 dyoubi
*/

#include "map.h"

#define CACHE_SIZE 5000

void readTileProps(t_tile *p_tile, const char *p_buf) {
    if (strcmp(p_buf, "plein") == 0) {
        p_tile->plein = 1;
        p_tile->etat = 'w';
    } else if (strcmp(p_buf, "vide") == 0) {
        p_tile->plein = 0;
        p_tile->type = 0;
        p_tile->etat = 0;
    } else if (strcmp(p_buf, "brick") == 0) {
        p_tile->plein = 1;
        p_tile->type = 'b';
    } else if (strcmp(p_buf, "floor") == 0) {
        p_tile->plein = 0;
        p_tile->type = 'g';
    } else if (strcmp(p_buf, "wall") == 0) {
        p_tile->plein = 1;
        p_tile->type = 'w';
    }
}

void chargerTileSet(FILE *p_file, t_map *p_map) {
    int tileCount, indexLargeur, indexHauteur;
    char buf[CACHE_SIZE];
    char buf2[CACHE_SIZE];
    SDL_RWops *rwop;

    rwop = SDL_RWFromFile("ressources/tilesets/tileset2.png", "rb");
    if (rwop == NULL) {
        perror("Impossible d'ouvrir le tileset");
        (EXIT_FAILURE);
    }


    p_map->tileset = IMG_LoadPNG_RW(rwop);
    if (p_map->tileset == NULL) {
        perror("Impossible d'ouvrir le tileset");
        exit(EXIT_FAILURE);
    }

    fscanf(p_file, "%d %d", &p_map->nbTilesX, &p_map->nbTilesY);
    p_map->sizeX = p_map->tileset->w / p_map->nbTilesX;
    p_map->sizeY = p_map->tileset->h / p_map->nbTilesY;

    p_map->props = malloc(p_map->nbTilesX * p_map->nbTilesY * sizeof(t_tile));
    for (indexHauteur = 0, tileCount = 0; indexHauteur < p_map->nbTilesY; ++indexHauteur) {
        for (indexLargeur = 0; indexLargeur < p_map->nbTilesX; ++indexLargeur, ++tileCount) {
            p_map->props[tileCount].rect.w = p_map->sizeX;
            p_map->props[tileCount].rect.h = p_map->sizeY;

            p_map->props[tileCount].rect.x = indexLargeur * p_map->sizeX;
            p_map->props[tileCount].rect.y = indexHauteur * p_map->sizeY;

            fscanf(p_file, "%s %s", buf, buf2);
            p_map->props[tileCount].plein = 0;
            readTileProps(&p_map->props[tileCount], buf2);
        }
    }

    p_map->texture = SDL_CreateTextureFromSurface(g_game_engine.renderer, p_map->tileset);
    if (!p_map->texture) {
        perror("Impossible d'ouvrir le tileset");
        exit(EXIT_FAILURE);
    }
}

void chargerLevel(FILE *p_file, t_map *p_map) {
    int indexLargeur, indexHauteur;
    int currentTile;

    fscanf(p_file, "%d %d", &p_map->nbTilesX, &p_map->nbTilesY);

    p_map->schema = malloc(p_map->nbTilesX * sizeof(t_tile_index *));

    for (indexLargeur = 0; indexLargeur < p_map->nbTilesX; indexLargeur++)
        p_map->schema[indexLargeur] = malloc(p_map->nbTilesX * sizeof(t_tile_index));

    for (indexHauteur = 0; indexHauteur < p_map->nbTilesY; indexHauteur++) {
        for (indexLargeur = 0; indexLargeur < p_map->nbTilesX; indexLargeur++) {
            fscanf(p_file, "%d", &currentTile);
            if (currentTile >= p_map->nbTilesX * p_map->nbTilesY)
                exit(EXIT_FAILURE);
            p_map->schema[indexLargeur][indexHauteur] = currentTile - 1;
        }
    }
}

t_map *chargerMap(const char *p_mapPath) {
    FILE *file;
    t_map *l_newMap;

    char buf[CACHE_SIZE];
    file = fopen(p_mapPath, "r");

    if (!file) {
        perror("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }
    SDL_Log("Le fichier est ouvert");
    fgets(buf, sizeof(buf), file);
    if (strstr(buf, "#Tilemapping Version 1.0") == NULL) {
        perror("Le format de fichier ne correspond pas");
        exit(EXIT_FAILURE);
    }
    l_newMap = malloc(sizeof(t_map));
    do {
        fgets(buf, CACHE_SIZE, file);
        if (strstr(buf, "#tilset#")) {
            chargerTileSet(file, l_newMap);
        }
        if (strstr(buf, "#level#")) {
            chargerLevel(file, l_newMap);
        }
    } while (strstr(buf, "#fin") == NULL);
    fclose(file);
    return l_newMap;
}

int afficherMap(t_map *p_map, SDL_Surface *p_screen) {

    SDL_Surface *surface = SDL_CreateRGBSurface(0,
                                                TILE_NUMBER_X * TILE_WIDTH,
                                                TILE_NUMBER_Y * TILE_HEIGHT,
                                                32,
                                                0, 0, 0, 0);

    int indexLargeur, indexHauteur;
    SDL_Rect rectDest;
    int numeroTile;

    for (indexLargeur = 0; indexLargeur < p_map->nbTilesX; ++indexLargeur) {
        for (indexHauteur = 0; indexHauteur < p_map->nbTilesY; ++indexHauteur) {
            rectDest.x = indexLargeur * p_map->sizeX;
            rectDest.y = indexHauteur * p_map->sizeY;
            numeroTile = p_map->schema[indexLargeur][indexHauteur];
            SDL_BlitSurface(p_map->tileset, &(p_map->props[numeroTile].rect), surface, &rectDest);
        }
    }
    p_map->texture = SDL_CreateTextureFromSurface(g_game_engine.renderer, surface);
    SDL_RenderCopy(g_game_engine.renderer, p_map->texture, NULL, NULL);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(p_map->texture);
    return EXIT_SUCCESS;
}

bool CollisionBox(t_map *p_map, SDL_Rect *p_player) {

    int coordsXmin, coordsXmax, coordsYmin, coordsYmax, indexX, indexY, indicetile;

    coordsXmin = p_player->x / TILE_WIDTH;
    coordsYmin = p_player->y / TILE_HEIGHT;

    coordsXmax = (p_player->x + p_player->w - 1) / p_map->sizeX;
    coordsYmax = (p_player->y + p_player->h - 1) / p_map->sizeY;

    if (coordsXmin < 0 || coordsYmin < 0) {
        return true;
    } else if (coordsXmax >= p_map->nbTilesX || coordsYmax >= p_map->nbTilesY) {
        return true;
    }

    for (indexY = coordsYmin; indexY <= coordsYmax; ++indexY) {
        for (indexX = coordsXmin; indexX <= coordsXmax; ++indexX) {
            indicetile = p_map->schema[indexX][indexY];
            if (p_map->props[indicetile].plein == 1) {
                return true;
            }
        }
    }
    return false;
}