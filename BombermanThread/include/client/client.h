/*
** client.h for Bomberman
** 
** Made by YOUBI David on 30/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 30 mai 09:37 2017 dyoubi
** Last update 30 mai 09:37 2017 dyoubi
*/

#ifndef BOMBERMAN_CLIENT_H
#define BOMBERMAN_CLIENT_H

SOCKET tryHost(const char *p_ip);
t_player_infos *confirmConnection(SOCKET sockfd);
#endif //BOMBERMAN_CLIENT_H
