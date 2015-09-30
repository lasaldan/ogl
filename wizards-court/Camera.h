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
#include <vector>
#include "Vertex.h"

class Camera {
    std::vector<float> lookFrom;
    std::vector<float> lookAt;
    std::vector<float> up;
    std::vector<float> U;
    std::vector<float> N;
    std::vector<float> V;
public:
    Camera();
    void setFromLocation(std::vector<float>);
    void setLookLocation(std::vector<float>);
    void setUp(std::vector<float>);
    
    void lookVertical(float);
    void lookHorizonal(float);
    // Omit rolling for now
    
    void moveHorizontal(float);
    void moveForward(float);
    void moveVertical(float);
    
    vector<float> Cross(vector<float>, vector<float>);
    vector<float> Minus(vector<float>, vector<float>);
    vector<float> Normalize(vector<float>);
    void RebuildMatrix();
    
    void calculateViewportEquivalent(Vertex);
};


#endif /* defined(__wizards_court__Camera__) */
