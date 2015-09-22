//
//  Game.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/21/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Game__
#define __wizards_court__Game__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include "SOIL.h"
#include "Scene.h"
#include "Item.h"
#include "ObjParser.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_LOCATION_X = 50;
const int SCREEN_LOCATION_Y = 50;

class Game {
    
private:
    bool Running;
    SDL_Window* viewport;
    SDL_GLContext context;
    GLuint texture[4];
    Scene scene;
    
public:
    Game();
    int Run();
    
private:
    bool Init();
    void HandleEvent(SDL_Event&);
    void Update();
    void Render();
    void Cleanup();
    void DrawScene();
    void DrawItem(Item, GLuint);
    void ImportModels();
    void LoadTextures();
    void SetCamera();
};

#endif /* defined(__wizards_court__Game__) */
