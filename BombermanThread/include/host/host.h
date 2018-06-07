//
// Created by David on 26/05/2017.
//

#ifndef BOMBERMAN_HOST_H
#define BOMBERMAN_HOST_H


#include <network/network.h>
#include <host/InterfaceHost.h>
#include <host/server.h>
#include "HostEvent.h"
#include "map.h"

void HostLoop();

int openSlot(int *p_index);

#endif //BOMBERMAN_HOST_H
