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

static int viewport;
Item crayonBox;
Item crayon1;
Item crayon2;
Item crayon3;

GLuint texture[4];

void createWindow();
void display();
void initializeSettings();
void setCamera();
void drawScene();
void importModels();
void loadTextures();

#endif
