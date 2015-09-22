//
//  Scene.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Scene__
#define __wizards_court__Scene__

#include <vector>
#include <stdio.h>
#include "PositionedItem.h"
#include "Item.h"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

class Scene {
private:
    std::vector<PositionedItem> Items;
public:
    Scene();
    void DrawScene();
    void DrawItem(PositionedItem);
    void AddItem(Item);
};

#endif /* defined(__wizards_court__Scene__) */
