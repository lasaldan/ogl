//
//  Face.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/16/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Face__
#define __wizards_court__Face__

#include <stdio.h>
#include "Vertex.h"
#include "TextureCoordinate.h"

#include <vector>
using namespace std;

class Face {
public:
    Face();
    vector<Vertex> vertices;
    vector<TextureCoordinate> textureCoordinates;
    void addVertex(Vertex);
    void addTextureCoordinate(TextureCoordinate);
};

#endif /* defined(__wizards_court__Face__) */
