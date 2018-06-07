//
// Created by David on 21/05/2017.
//

#ifndef BOMBERCLIENT_MENU_H
#define BOMBERCLIENT_MENU_H

#include "globals.h"
#include "actionsMenu.h"

typedef struct s_menu {
    int currentSelected;        //Index vers le menu selectionne
    int size;
    bool isCurrent;
    bool showMenu;              // Si le menu doit être affiche
    char *menuName;
    struct s_menu *parentMenu;  // Pointeur vers le menu parent
    struct s_menu_item **listItem;
} t_menu;

typedef struct s_menu_item {
    bool isSelected;            //Si l'item est selectionne
    char *itemName;
    SDL_Rect rectText;
    SDL_Rect rectBackground;
    SDL_Texture *text;
    SDL_Texture *background;
    SDL_Texture *textSelected;
    struct s_menu *subMenu;     //Pointeur vers un sous menu
    void (*action)(void);       // L'item peut lancer une action
} t_menu_item;

typedef struct s_menu_screen {

} t_menu_screen;

t_menu_item *createMenuItem(char *p_itemName, void *p_action, t_menu *p_subMenu);

t_menu *createMenu(char *p_menuName, int p_listSize, t_menu *p_parentMenu);

void initMainMenu();

void drawMenu(t_menu *p_menu);


#endif //BOMBERCLIENT_MENU_H
