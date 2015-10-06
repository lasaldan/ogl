//
//  Transformation.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__Transformation__
#define __wizards_court__Transformation__

#include <stdio.h>
#include <vector>
#include "Matrix.h"
#include "Vertex.h"

class Transformation {
private:
    Matrix scale;
    Matrix translate;
    Matrix rotateX;
    Matrix rotateY;
    Matrix rotateZ;
    Matrix transformationMatrix;
    Matrix inverseTransformationMatrix;
public:
    Transformation();
    Matrix Translate(float, float, float);
    Matrix RotateX(float);
    Matrix RotateY(float);
    Matrix RotateZ(float);
    Matrix Scale(float);
    Vertex LocalToWorld(Vertex);
    Vertex WorldToLocal(Vertex);
private:
    Matrix CalculateTransformationMatrices();
};


#endif /* defined(__wizards_court__Transformation__) */
