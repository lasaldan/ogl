//
//  Controller.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/19/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Controller__
#define __wizards_court__Controller__

#include <stdio.h>
#include "SDL2/SDL.h"

class Controller {
public:
    SDL_Event sdlEvent;
    Controller();
    void Event();
    void OnEvent(SDL_Event* Event);
    void OnLButtonDown(int, int);
};

#endif /* defined(__wizards_court__Controller__) */
