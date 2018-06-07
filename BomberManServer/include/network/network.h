/*
** network.h for ClientServer
** 
** Made by YOUBI David on 15/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 15 mai 14:16 2017 dyoubi
** Last update 15 mai 14:16 2017 dyoubi
*/

#ifndef CLIENTSERVER_NETWORK_H
#define CLIENTSERVER_NETWORK_H

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

#include "client.h"
#include "server.h"
#include "protocol_client.h"
#include "globals.h"
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

int runClient(int argc, char *argv[]);

void init(void);

void end(void);

int create_server(int port);
int accept_client(int p_server);

int matchMaking(void *p_tabPort);
#endif //CLIENTSERVER_NETWORK_H
