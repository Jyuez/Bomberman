//
// Created by David on 21/05/2017.
//

#include <game/menuTree/menu.h>
#include "mainLoop.h"

void runGame() {
    bool run = true;
    SDL_Event event;

    getCurrentMenu()->showMenu = true;
    while (run) {
        SDL_RenderClear(getRenderer());
        run = EventHandler(&event);
        drawMenu(getCurrentMenu());
        SDL_RenderPresent(getRenderer());
    }
}