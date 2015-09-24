//
//  Camera.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Camera__
#define __wizards_court__Camera__

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

class Camera {
    float angle;
public:
    Camera();
    void AdjustCamera();
};


#endif /* defined(__wizards_court__Camera__) */
