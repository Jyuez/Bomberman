//
// Created by David on 26/05/2017.
//

#ifndef BOMBERMAN_MENU_H
#define BOMBERMAN_MENU_H

#include "defs.h"
#include "sharde.h"

t_menu *createMenu(char *p_menuName, int p_listSize);
int createMenuItem(t_menu *p_menu, int p_menuSize);
void drawMenu(t_menu *p_menu);
bool allocateMenuMemory(t_menu *p_menu, int p_menuSize);
void clearMenu(t_menu *p_menu);
#endif //BOMBERMAN_MENU_H
