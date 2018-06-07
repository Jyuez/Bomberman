/*
** ActionLauncher.h for Bomberman
** 
** Made by YOUBI David on 23/05/2017
** login <youbi_d@etna-alternance.net>
**
** Started on 23 mai 11:03 2017 dyoubi
** Last update 23 mai 11:03 2017 dyoubi
*/

#ifndef BOMBERMAN_ACTIONLAUNCHER_H
#define BOMBERMAN_ACTIONLAUNCHER_H

#include "InterfaceLauncher.h"

void reachSubMenu(t_menu *p_menu);
void reachParentMenu(t_menu *p_menu);

void runHostMode();

void runClientMode();

#endif //BOMBERMAN_ACTIONLAUNCHER_H
