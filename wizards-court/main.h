//
//  project2.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/15/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef wizards_court_project2_h
#define wizards_court_project2_h

#include "ObjParser.h"
#include "Controller.h"
#include <stdio.h>
#include <SDL2/SDL.h>



static int viewport;
Item parking_lot;
Item car;
Item tire1;
Item tire2;
Item tire3;
Item tire4;

GLuint texture[4];

Controller controller;

void createWindow();
void display();
void initializeSettings();
void setCamera();
void drawScene();
void importModels();
void loadTextures();
void handleEvents();
void drawItem(Item, GLuint);

#endif
