//
// Created by David on 21/05/2017.
//

#ifndef BOMBERCLIENT_EVENTHANDLER_H
#define BOMBERCLIENT_EVENTHANDLER_H

#include "globals.h"

typedef struct  s_input {
    const Uint8   *keyState;
    SDL_KeyboardEvent keyboardEvent;
    bool    quit;
}               t_input;

bool EventHandler(SDL_Event *p_event);

#endif //BOMBERCLIENT_EVENTHANDLER_H
