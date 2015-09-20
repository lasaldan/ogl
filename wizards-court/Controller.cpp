//
//  Controller.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/19/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include <iostream>
#include "Controller.h"
using namespace std;

Controller::Controller() {
    
}

void Controller::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
    }
}

void Controller::OnLButtonDown(int mX, int mY) {
    cout << mX << mY << endl;
}