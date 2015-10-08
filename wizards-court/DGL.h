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
#include "Face.h"
#include "Vector.h"
#include "Vertex.h"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

#define MODEL 0
#define CAMERA 1

class DGL {
    
private:
    DGL();
    int mode;
    
public:
    void setMode(int);
    void setTexture(unsigned int);
    
    void translateX(float);
    void translateY(float);
    void translateZ(float);
    
    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);
    
    void scaleX(float);
    void scaleY(float);
    void scaleZ(float);
    
    void drawFace(Face);
    void drawFaces(std::vector<Face>);
    
    void setNearClip();
    void setFarClip();
    
private:    
    Matrix objRotateX;
    Matrix objRotateY;
    Matrix objRotateZ;
    Matrix objScale;
    Matrix objTranslate;
    Matrix objTransformation;
    Matrix objInverseTransformation;
    
    Matrix viewRotateX;
    Matrix viewRotateY;
    Matrix viewRotateZ;
    Matrix viewScale;
    Matrix viewTranslate;
    Matrix viewTransformation;
    Matrix viewInverseTransformation;
    
    Matrix Perspective;
    
    Matrix calculateObjectTransformation();
    Matrix calculateObjectInverseTransformation();
    
    float toRadians(float);
    float toDegrees(float);
    
    Vertex objToWorld(Vertex);
    Vertex worldToView(Vertex);
    
};

#endif /* defined(__wizards_court__DGL__) */
