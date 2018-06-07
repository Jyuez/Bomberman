//
// Created by David on 21/05/2017.
//

#include <game/menuTree/menu.h>
#include "EventHandler.h"

bool HandleMenuEvent(SDL_Event *p_event) {

    static bool keepRun = true;
    bool trigerMenu = false;

    int currentChoice = getCurrentMenu()->currentSelected;
    t_menu *currentMenu = getCurrentMenu();

    for (int index = 0; index < currentMenu->size; ++index) {
        currentMenu->listItem[index]->isSelected = false;
    }
    /* Keymapping : gere les appuis sur les touches et les enregistre
    dans la structure input */
    while (SDL_PollEvent(p_event)) {
        switch (p_event->type) {
            case SDL_KEYDOWN:
                switch (p_event->key.keysym.sym) {
                    case SDLK_UP:
                        if (currentChoice > 0) currentChoice--;
                        break;
                    case SDLK_DOWN:
                        if (currentChoice < currentMenu->size - 1) currentChoice++;
                        break;
                    case SDLK_ESCAPE:
                        keepRun = false;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (p_event->key.keysym.sym) {
                    case SDLK_RETURN:
                        //SDL_Log("Menu event: return\n");
                        trigerMenu = true;
                        break;
                    case SDLK_SPACE:
                        //SDL_Log("Menu event: space\n");
                        break;
                    case SDLK_p:
                        //SDL_Log("Game event: p \n");
                        //currentMenu->showMenu = false;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    currentMenu->currentSelected = currentChoice;
    currentMenu->listItem[currentChoice]->isSelected = true;

    if (trigerMenu && currentMenu->listItem[currentChoice]->action != NULL) {
        (*currentMenu->listItem[currentChoice]->action)();
        //SDL_Log("Run action\n");
    }
    return keepRun;
}

bool EventHandler(SDL_Event *p_event) {


    t_menu *currentMenu = getCurrentMenu();
    if (currentMenu->showMenu) {
        if (HandleMenuEvent(p_event))
            return true;
        else return false;
    }
    return true;
}