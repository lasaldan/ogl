//
//  TransformationMatrix.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__TransformationMatrix__
#define __wizards_court__TransformationMatrix__

#include <stdio.h>
#include <vector>
#include "Vertex.h"
#include <math.h>       /* sin */

#define PI 3.14159265358979
using namespace std;

class TransformationMatrix {
private:
    vector< vector< float > > matrixData;
public:
    TransformationMatrix();
    vector< vector< float > > GetMatrix();
    vector< vector< float > > Cross(TransformationMatrix);
    vector< vector< float > > Dot(TransformationMatrix);
    vector< vector< float > > Multiply(TransformationMatrix);
    void Translate(float, float, float);
    void RotateX(float);
    void RotateY(float);
    void RotateZ(float);
    void Scale(float);
    Vertex Transform(Vertex);
    void setValue(int, int, float);
};


#endif /* defined(__wizards_court__TransformationMatrix__) */
