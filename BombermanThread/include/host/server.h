//
// Created by David on 23/05/2017.
//

#ifndef BOMBERMAN_SERVER_H
#define BOMBERMAN_SERVER_H

bool initClient(t_client_player *p_client, t_player_infos *player_infos);
void serverLoop(t_client_player *p_client, t_player_infos *p_player_infos);
int startupServer();
int dockClient(t_client_player *p_client_player);
#endif //BOMBERMAN_SERVER_H
