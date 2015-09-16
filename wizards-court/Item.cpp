//
//  Item.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/15/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Item.h"
#include <stdio.h>
using namespace std;


Item::Item() {
}

void Item::AddVertex(Vertex v){
    vertices.push_back(v);

}

void Item::AddTextureCoodinate(TextureCoordinate t){
    textureCoordinates.push_back(t);
}

std::vector<Vertex> Item::GetVertices(){
    return vertices;
}

std::vector<TextureCoordinate> Item::GetTextureCoordinates(){
    return textureCoordinates;
}
