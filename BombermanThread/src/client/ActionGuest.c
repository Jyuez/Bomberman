/*
** ActionGuest.c for Bomberman
** 
** Made by YOUBI David on 29/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 29 mai 14:42 2017 dyoubi
** Last update 29 mai 14:42 2017 dyoubi
*/

#include <SDL2/SDL_keyboard.h>
#include <defs.h>
#include <GameEngine/engine.h>
#include <sharde.h>
#include <client/client.h>
#include "ActionGuest.h"

void chooseServer() {
    bool run;

    run = true;
    SDL_StartTextInput();
    g_game.ipHost[0] = '\0';
    while (run) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                        case SDLK_RETURN2:
                        case SDLK_ESCAPE:
                            SDL_StopTextInput();
                            run = false;
                            printf("%s\n", g_game.ipHost);
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_QUIT:
                    SDL_StopTextInput();
                    run = false;
                    break;
                case SDL_TEXTINPUT:
                    strcat(g_game.ipHost, event.text.text);
                    break;
                default:
                    break;
            }
        }
    }
    SDL_StopTextInput();
}


/*Cette fonction essaie de se connecter au serveur.
 * Si la connexion reussie, le joueur est initialiser et entre en attente du debut de la partie*/
void connectToHost() {
    SOCKET sockfd;
    t_player_infos *player;
    pthread_mutex_lock(&g_game.mutex);
    sockfd = tryHost(g_game.ipHost);
    pthread_mutex_unlock(&g_game.mutex);

    if(sockfd != EXIT_FAILURE){
        player = confirmConnection(sockfd);
        printf("Bombs left: %d\nMax speed: %d\n", player->bombs_left, player->max_speed);
    } else {
        //TODO: Afficher des infos sur le serveur
    }
}