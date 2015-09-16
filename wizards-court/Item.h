//
//  Item.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/15/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Item__
#define __wizards_court__Item__

#include <stdio.h>
#include <vector>
#include "vertex.h"
#include "TextureCoordinate.h"

class Item {
public:
    std::vector<Vertex> vertices;
    std::vector<TextureCoordinate> textureCoordinates;
    Item();
    void AddVertex(Vertex);
    void AddTextureCoodinate(TextureCoordinate);
    std::vector<Vertex> GetVertices();
    std::vector<TextureCoordinate> GetTextureCoordinates();
};



#endif /* defined(__wizards_court__Item__) */
