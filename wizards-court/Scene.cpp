//
//  Scene.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Scene.h"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
using namespace std;

Scene::Scene() {
}


void Scene::DrawItem(PositionedItem posItem) {
    Item item = posItem.GetItem();
    // move item
    // rotate item
    glBindTexture(GL_TEXTURE_2D, item.texture);
    for(int i=0; i<item.faces.size(); i++) {
        glBegin(GL_POLYGON);
        for(int j=0; j<item.faces[i].vertices.size(); j++) {
            glTexCoord2f(item.faces[i].textureCoordinates[j].x, item.faces[i].textureCoordinates[j].y);
            Vertex translated = posItem.GetMatrix().Transform(item.faces[i].vertices[j]);;
            glVertex3f(translated.x-1, translated.y-1, translated.z-2);
        }
        glEnd();
    }
}

PositionedItem& Scene::Get(string i) {
    return Items.at(i);
}


void Scene::DrawScene() {
    glClear (GL_COLOR_BUFFER_BIT);
    
    for (map<string, PositionedItem>::iterator it = Items.begin() ; it != Items.end(); ++it)
        DrawItem(it->second);
    
    glFlush ();
}

PositionedItem& Scene::AddItem(string name, Item item) {
    PositionedItem pi = PositionedItem(item);
    Items.insert( pair<string, PositionedItem>(name, pi) );
    return Items.at(name);
}