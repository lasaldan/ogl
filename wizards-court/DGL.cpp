//
//  DGL.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 10/6/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "DGL.h"
using namespace std;


/************
 * Sets the mode.
 * 0 = object mode
 * 1 = camera mode
 * Transformation functions modify the matrix that cooresponds to the current mode
 ************/
void
DGL::setMode(int newMode) {
    
    if( newMode != MODEL && newMode > CAMERA )
        return;
    
    mode = newMode;
}


/************
 * Set current texture
 ************/
void
DGL::setTexture(unsigned int id) {
    glBindTexture(GL_TEXTURE_2D, id);
}


/************
 * Modify the current mode's translation matrix X value
 ************/
void
DGL::translateX(float val) {
    switch (mode) {
        case MODEL:
            objTranslate.Set(0,3,val);
            break;
            
        case CAMERA:
            viewTranslate.Set(0,3,val);
            break;
    }
}


/************
 * Modify the current mode's translation matrix Y value
 ************/
void
DGL::translateY(float val) {
    switch (mode) {
        case MODEL:
            objTranslate.Set(1,3,val);
            break;
            
        case CAMERA:
            viewTranslate.Set(1,3,val);
            break;
    }
}


/************
 * Modify the current mode's translation matrix Z value
 ************/
void
DGL::translateZ(float val) {
    switch (mode) {
        case MODEL:
            objTranslate.Set(1,3,val);
            break;
            
        case CAMERA:
            viewTranslate.Set(1,3,val);
            break;
    }
}


/************
 * Modify the current mode's rotateX matrix
 ************/
void
DGL::rotateX(float degrees) {
    switch (mode) {
        case MODEL:
            objRotateX.Set(1, 1, cos( toRadians(degrees) ));
            objRotateX.Set(1, 2, sin( toRadians(degrees) ));
            objRotateX.Set(2, 1, -sin( toRadians(degrees) ));
            objRotateX.Set(2, 2, cos( toRadians(degrees) ));
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modify the current mode's rotateY matrix
 ************/
void
DGL::rotateY(float degrees) {
    switch (mode) {
        case MODEL:
            objRotateY.Set(0, 0, cos( toRadians(degrees) ));
            objRotateY.Set(0, 2, -sin( toRadians(degrees) ));
            objRotateY.Set(2, 0, sin( toRadians(degrees) ));
            objRotateY.Set(2, 2, cos( toRadians(degrees) ));
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modify the current mode's rotateZ matrix
 ************/
void
DGL::rotateZ(float degrees) {
    switch (mode) {
        case MODEL:
            objRotateZ.Set(0, 0, cos( toRadians(degrees) ));
            objRotateZ.Set(0, 1, sin( toRadians(degrees) ));
            objRotateZ.Set(1, 0, -sin( toRadians(degrees) ));
            objRotateZ.Set(1, 1, cos( toRadians(degrees) ));
            break;
            
        case CAMERA:
            break;
    }
    
}


/************
 * Modify the current mode's scale matrix X value
 ************/
void
DGL::scaleX(float val) {
    switch (mode) {
        case MODEL:
            objScale.Set(0,0,val);
            break;
            
        case CAMERA:
            viewScale.Set(0,0,val);
            break;
    }
}


/************
 * Modify the current mode's scale matrix Y value
 ************/
void
DGL::scaleY(float val) {
    switch (mode) {
        case MODEL:
            objScale.Set(1,1,val);
            break;
            
        case CAMERA:
            viewScale.Set(1,1,val);
            break;
    }
}


/************
 * Modify the current mode's scale matrix Z value
 ************/
void
DGL::scaleZ(float val) {
    switch (mode) {
        case MODEL:
            objScale.Set(2,2,val);
            break;
            
        case CAMERA:
            viewScale.Set(2,2,val);
            break;
    }
}


/************
 * Draw a single face using current pipeline settings
 ************/
void
DGL::drawFace(Face face){
    
    glBegin(GL_POLYGON);
    
    for(int i = 0; i < face.vertices.size(); i ++) {
        glTexCoord2f(face.textureCoordinates[i].x, face.textureCoordinates[i].y);
        Vertex transformed = worldToView( objToWorld ( face.vertices[i] ) );
        glVertex3f(transformed.x, transformed.y, transformed.z);
    }
    
    glEnd();
}


/************
 * Draw all faces in vector using current pipeline settings
 ************/
void
DGL::drawFaces(vector<Face> faces){
    
    for (auto& face: faces) {
        drawFace(face);
    }
}

void
DGL::setNearClip(){
    
}

void
DGL::setFarClip(){
    
}


/************
 * Convert degrees to radians
 ************/
float
DGL::toRadians(float degrees) {
    return PI * degrees / 180;
}


/************
 * Convert radians to degrees
 ************/
float
DGL::toDegrees(float radians) {
    return radians * 180 / PI;
}
