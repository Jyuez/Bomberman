//
// Created by David on 26/05/2017.
//

#include "HostEvent.h"

bool EventHandlerHost(SDL_Event *p_event, t_menu *p_menu) {

    static bool keepRun;
    static bool trigerMenu;

    trigerMenu = false;
    keepRun = true;

    /* Keymapping : gere les appuis sur les touches et les enregistre
    dans la structure input */
    while (SDL_PollEvent(p_event)) {
        switch (p_event->type) {
            case SDL_KEYDOWN:
                switch (p_event->key.keysym.sym) {
                    case SDLK_UP:
                        if (p_menu->currentSelected > 0) p_menu->currentSelected--;
                        break;
                    case SDLK_DOWN:
                        if (p_menu->currentSelected < p_menu->size - 1) p_menu->currentSelected++;
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
                        SDL_Log("Menu event: return\n");
                        trigerMenu = true;
                        break;
                    case SDLK_SPACE:
                        //SDL_Log("Menu event: space\n");
                        break;
                    case SDLK_p:
                        //SDL_Log("Game event: p \n");
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    if (trigerMenu) {
        if (p_menu->actionList[p_menu->currentSelected] != NULL)
            p_menu->actionList[p_menu->currentSelected]();
        else printf("Pas d'actionsList possible\n");
    }

    return keepRun;
}