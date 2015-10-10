//
//  DGLCamera.h
//  wizards-court
//
//  Created by Daniel Fuller on 10/9/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__DGLCamera__
#define __wizards_court__DGLCamera__

#include <stdio.h>
#include "Vertex.h"

class DGLCamera {
public:
    DGLCamera();
    Vertex position;
    float rotationX;
    float rotationY;
};

#endif /* defined(__wizards_court__DGLCamera__) */
