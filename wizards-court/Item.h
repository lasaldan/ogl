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
#include "Vertex.h"
#include "TextureCoordinate.h"
#include "Face.h"

class Item {
public:
    std::vector<Vertex> vertices;
    std::vector<TextureCoordinate> textureCoordinates;
    std::vector<Face> faces;
    Item();
    void AddVertex(Vertex);
    void AddFace(Face);
    void AddTextureCoodinate(TextureCoordinate);
    std::vector<Vertex> GetVertices();
    std::vector<TextureCoordinate> GetTextureCoordinates();
    std::vector<Face> GetFaces();
};



#endif /* defined(__wizards_court__Item__) */
