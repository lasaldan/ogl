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
#include "Matrix.h"
#include "Vertex.h"

class Camera {
    float angle;
    std::vector<float> lookFrom;
    std::vector<float> lookAt;
    std::vector<float> up;
    std::vector<float> U;
    std::vector<float> N;
    std::vector<float> V;
    Matrix translation;
    Matrix changeOfBase;
    Matrix viewMatrix;
    Matrix perspective;
    float far;
    float near;
    float left;
    float right;
    float top;
    float bottom;
    float fov;
public:
    Camera();
    void setFromLocation(std::vector<float>);
    void setLookLocation(std::vector<float>);
    void setUp(std::vector<float>);
    
    void lookVertical(float);
    void lookHorizontal(float);
    // Omit rolling for now
    
    void moveHorizontal(float);
    void moveForward(float);
    void moveVertical(float);
    
    vector<float> Cross(vector<float>, vector<float>);
    vector<float> Minus(vector<float>, vector<float>);
    vector<float> Normalize(vector<float>);
    void RebuildMatrix();
    
    Vertex transform(Vertex);
};


#endif /* defined(__wizards_court__Camera__) */
