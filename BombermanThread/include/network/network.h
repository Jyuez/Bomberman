//
// Created by David on 23/05/2017.
//

#ifndef BOMBERMAN_NETWORK_H
#define BOMBERMAN_NETWORK_H

#include "defs.h"
#include "structs.h"

void initNetwork(void);

void end(void);
t_player_infos *getSendableInfos(t_player_infos *p_player_infos);
t_player_infos *getReadbleInfos(t_player_infos *p_player_infos);
#endif //BOMBERMAN_NETWORK_H
