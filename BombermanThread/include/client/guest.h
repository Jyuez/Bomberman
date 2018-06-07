/*
** guest.h for Bomberman
** 
** Made by YOUBI David on 29/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 29 mai 12:31 2017 dyoubi
** Last update 29 mai 12:31 2017 dyoubi
*/

#ifndef BOMBERMAN_GUEST_H
#define BOMBERMAN_GUEST_H

#include <network/network.h>
#include "InterfaceGuest.h"
#include <client/guestEvent.h>

int guestLoop();
void renderGuestScreen(t_menu* p_menu);
#endif //BOMBERMAN_GUEST_H
