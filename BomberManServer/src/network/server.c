//
// Created by David on 21/05/2017.
//

#include <game/player.h>
#include <game/mainLoop.h>
#include "server.h"

#define MAX_SIZE 50
#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(b1, b2, len) (memmove((b2), (b1), (len)), (void) 0)

typedef struct s_player_client{

    pthread_mutex_t exitMutex;
    pthread_mutex_t dataMutex;

    t_player_infos *player;

    //t_client_request *request;
}t_player_client;


int create_server(int port) {
    int socketServer;
    struct sockaddr_in sin;

    if ((socketServer = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        exit(-1);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(socketServer, (struct sockaddr *) &sin, sizeof(sin)) < 0)
        exit(-1);
    if (listen(socketServer, MAX_PLAYER) < 0)
        exit(EXIT_FAILURE);
    return (socketServer);
}

int accept_client(int p_server) {
    int client;
    struct sockaddr_in sin;
    int size;

    size = sizeof(sin);
    if ((client = accept(p_server, (struct sockaddr *) &sin, &size)) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Le client n'a pas pu se connecter...\n");
        return(EXIT_FAILURE);
    } else printf("[DEBUG]New client is connected\n");
    return (client);
}


int matchMaking(void *p_tabPort) {

    int portTab[MAX_PLAYER - 1] = {PORT_1, PORT_2, PORT_3};
    static pthread_mutex_t mutex;
    pthread_t *threadCommunication;
    t_game *gameState;

    mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    gameState = getGame();

    if (gameState == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game state isn't ready\n");
        return EXIT_FAILURE;
    }

    init();

    gameState->isMatchmaking = true;
    pthread_mutex_unlock(&mutex);

    /*TODO: Matchmaking:
     * Etape 1: Lancer 3 thread d'interaction en simultané
     * Etape 2: Attendre le debut de la partie
     * Etape 3: Quand la partie demarre, le matchmaker tue les threads non connecte
     **/

    //THREAD D'ECOUTE
    for (int index = 0; index < MAX_PLAYER; ++index) {
        // - 1 Attendre une connexion sur le port courant
        printf("Ouverture du nouveau port d'ecoute %d...\n", index + 1);
        int newSocket = create_server(portTab[index]);
        if (newSocket == EXIT_FAILURE) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Impossible d'ouvrir un port d'écoute\n");
        } else accept_client(newSocket);

        //Assignation du joueur
        pthread_mutex_lock(mutex);
        gameState->player_infos[index].socket = newSocket;
        gameState->player_infos[index].connected = true;
        pthread_mutex_unlock(mutex);
        printf("Un nouveau joueur s'est connecte sur le port %d (%d). ID: %d\n", index + 1, portTab[index], newSocket);

        //TODO: Lancer le thread de communication
    }
        pthread_exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

void playerCommunication(t_player_infos *p_playerToHandle) {
    static  pthread_mutex_t mutex;
    static  t_game *game;
    bool    run;
    run = true;
    mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(mutex);
    game = getGame();
    pthread_mutex_unlock(mutex);

    while (run){
        pthread_mutex_lock(mutex);
        run = game->inParty;
        pthread_mutex_unlock(mutex);
        sleep(5);
    }
}