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
using namespace std;

class TransformationMatrix {
private:
    vector< vector< float > > matrixData;
public:
    TransformationMatrix();
    TransformationMatrix GetMatrix();
    TransformationMatrix Cross(TransformationMatrix);
    TransformationMatrix Dot(TransformationMatrix);
    void SetTranslation(Vertex);
    void SetRotation(float, float, float);
    void SetScale(float);
    void AddTranslation(float, float, float);
    void AddRotation(float, float, float);
    void AddScale(float);
    Vertex Transform(Vertex);
};


#endif /* defined(__wizards_court__TransformationMatrix__) */
