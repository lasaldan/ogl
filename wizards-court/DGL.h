//
//  DGL.h
//  wizards-court
//
//  Created by Daniel Fuller on 10/6/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__DGL__
#define __wizards_court__DGL__

#include <stdio.h>
#include "Matrix.h"
#include "Transformation.h"

#define MODEL 0
#define VIEW 1
#define PROJECTION 2

class DGL {
private:
    DGL();
    int mode;
public:
    Matrix WorldToView;
    Matrix ViewToWorld;
    
    Matrix ObjectToWorld;
    Matrix WorldToObject;
    
    void SetMode(int);
    
    void SetTransformation(Transformation);
};

#endif /* defined(__wizards_court__DGL__) */
