//
//  DGL.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 10/6/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "DGL.h"
using namespace std;

// Initialize all static members
Matrix DGL::objRotateX;
Matrix DGL::objRotateY;
Matrix DGL::objRotateZ;
Matrix DGL::objScale;
Matrix DGL::objTranslate;
Matrix DGL::viewRotateX;
Matrix DGL::viewRotateY;
Matrix DGL::viewRotateZ;
Matrix DGL::viewScale;
Matrix DGL::viewTranslate;
Matrix DGL::perspective;
Matrix DGL::objTransformation;
Matrix DGL::viewTransformation;
Matrix DGL::objInverseTransformation;
Matrix DGL::viewInverseTransformation;
int DGL::mode;
bool DGL::objMatrixDirty;
bool DGL::viewMatrixDirty;


/************
 * Initializes DGL since everything's static and private constructor
 ************/
void
DGL::init() {
    objMatrixDirty = true;
    viewMatrixDirty = true;
    objRotateX = Matrix::Identity();
    objRotateY = Matrix::Identity();
    objRotateZ = Matrix::Identity();
    objScale = Matrix::Identity();
    objTranslate = Matrix::Identity();
    objTransformation = Matrix::Identity();
    objInverseTransformation = Matrix::Identity();
    
    viewRotateX = Matrix::Identity();
    viewRotateY = Matrix::Identity();
    viewRotateZ = Matrix::Identity();
    viewScale = Matrix::Identity();
    viewTranslate = Matrix::Identity();
    viewTransformation = Matrix::Identity();
    viewInverseTransformation = Matrix::Identity();
    
    perspective = Matrix();
}


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
 * Sets current texture
 ************/
void
DGL::setTexture(unsigned int id) {
    glBindTexture(GL_TEXTURE_2D, id);
}


/************
 * Modifies the current mode's translation matrices
 ************/
void
DGL::translateXYZ(float valX, float valY, float valZ) {
    switch (mode) {
        case MODEL:
            translateX(valX);
            translateY(valY);
            translateZ(valZ);
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modifies the current mode's translation matrix X value
 ************/
void
DGL::translateX(float val) {
    switch (mode) {
        case MODEL:
            objTranslate.Set(0,3,val);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            viewTranslate.Set(0,3,val);
            break;
    }
}


/************
 * Modifies the current mode's translation matrix Y value
 ************/
void
DGL::translateY(float val) {
    switch (mode) {
        case MODEL:
            objTranslate.Set(1,3,val);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            viewTranslate.Set(1,3,val);
            break;
    }
}


/************
 * Modifies the current mode's translation matrix Z value
 ************/
void
DGL::translateZ(float val) {
    switch (mode) {
        case MODEL:
            objTranslate.Set(2,3,val);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            viewTranslate.Set(2,3,val);
            break;
    }
}


/************
 * Modifies the current mode's rotation matrices
 ************/
void
DGL::rotateXYZ(float degX, float degY, float degZ) {
    switch (mode) {
        case MODEL:
            rotateX(degX);
            rotateY(degY);
            rotateZ(degZ);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modifies the current mode's rotateX matrix
 ************/
void
DGL::rotateX(float degrees) {
    switch (mode) {
        case MODEL:
            objRotateX.Set(1, 1, cos( toRadians(degrees) ));
            objRotateX.Set(1, 2, sin( toRadians(degrees) ));
            objRotateX.Set(2, 1, -sin( toRadians(degrees) ));
            objRotateX.Set(2, 2, cos( toRadians(degrees) ));
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modifies the current mode's rotateY matrix
 ************/
void
DGL::rotateY(float degrees) {
    switch (mode) {
        case MODEL:
            objRotateY.Set(0, 0, cos( toRadians(degrees) ));
            objRotateY.Set(0, 2, -sin( toRadians(degrees) ));
            objRotateY.Set(2, 0, sin( toRadians(degrees) ));
            objRotateY.Set(2, 2, cos( toRadians(degrees) ));
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modifies the current mode's rotateZ matrix
 ************/
void
DGL::rotateZ(float degrees) {
    switch (mode) {
        case MODEL:
            objRotateZ.Set(0, 0, cos( toRadians(degrees) ));
            objRotateZ.Set(0, 1, sin( toRadians(degrees) ));
            objRotateZ.Set(1, 0, -sin( toRadians(degrees) ));
            objRotateZ.Set(1, 1, cos( toRadians(degrees) ));
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            break;
    }
    
}


/************
 * Modifies the current mode's scale matrices
 ************/
void
DGL::scaleXYZ(float valX, float valY, float valZ) {
    switch (mode) {
        case MODEL:
            scaleX(valX);
            scaleY(valY);
            scaleZ(valZ);
            break;
            
        case CAMERA:
            break;
    }
}


/************
 * Modifies the current mode's scale matrix X value
 ************/
void
DGL::scaleX(float val) {
    switch (mode) {
        case MODEL:
            objScale.Set(0,0,val);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            viewScale.Set(0,0,val);
            break;
    }
}


/************
 * Modifies the current mode's scale matrix Y value
 ************/
void
DGL::scaleY(float val) {
    switch (mode) {
        case MODEL:
            objScale.Set(1,1,val);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            viewScale.Set(1,1,val);
            break;
    }
}


/************
 * Modifies the current mode's scale matrix Z value
 ************/
void
DGL::scaleZ(float val) {
    switch (mode) {
        case MODEL:
            objScale.Set(2,2,val);
            objMatrixDirty = true;
            break;
            
        case CAMERA:
            viewScale.Set(2,2,val);
            break;
    }
}


/************
 * Draws a single face using current pipeline settings
 ************/
void
DGL::drawFace(Face face){
    
    if(objMatrixDirty)
        calculateObjectTransformation();
    
    glBegin(GL_POLYGON);
    
    for(int i = 0; i < face.vertices.size(); i ++) {
        glTexCoord2f(face.textureCoordinates[i].x, face.textureCoordinates[i].y);
        Vertex transformed = worldToView( objToWorld ( face.vertices[i] ) );
        glVertex3f(transformed.x, transformed.y, transformed.z);
    }
    
    glEnd();
}


/************
 * Draws all faces in vector using current pipeline settings
 ************/
void
DGL::drawFaces(vector<Face> faces){
    
    for (auto& face: faces) {
        drawFace(face);
    }
}


/************
 * Draws all faces in an item using current pipeline settings
 ************/
void
DGL::drawItem(Item item){
    
    for (auto& face: item.faces) {
        drawFace(face);
    }
}


/************
 * Draws all items in the scene using current pipeline settings
 ************/
void
DGL::drawScene(Scene scene){
    
    int preMode = mode;
    mode = 0;
    
    for (auto& item: scene.Items) {
        Item obj = item.second;
        
        setTexture(obj.texture);
        
        rotateXYZ(obj.rotationX, obj.rotationY, obj.rotationZ);
        translateXYZ(obj.translationX, obj.translationY, obj.translationZ);
        scaleXYZ(obj.scalationX, obj.scalationY, obj.scalationZ);
        
        drawItem(obj);
    }
    
    mode = preMode;
}


Vertex DGL::objToWorld( Vertex v ) {
    float x =   (objTransformation.Get(0,0) * v.getX() +
                 objTransformation.Get(0,1) * v.getY() +
                 objTransformation.Get(0,2) * v.getZ() +
                 objTransformation.Get(0,3));
    
    float y =   (objTransformation.Get(1,0) * v.getX() +
                 objTransformation.Get(1,1) * v.getY() +
                 objTransformation.Get(1,2) * v.getZ() +
                 objTransformation.Get(1,3));
    
    float z =   (objTransformation.Get(2,0) * v.getX() +
                 objTransformation.Get(2,1) * v.getY() +
                 objTransformation.Get(2,2) * v.getZ() +
                 objTransformation.Get(2,3));
    return Vertex(x,y,z);
}

Vertex DGL::worldToView( Vertex v ) {
    return v;
}


/************
 * Converts degrees to radians
 ************/
float
DGL::toRadians(float degrees) {
    return PI * degrees / 180;
}


/************
 * Converts radians to degrees
 ************/
float
DGL::toDegrees(float radians) {
    return radians * 180 / PI;
}


/************
 * Calculates object transformation matrix
 ************/
Matrix
DGL::calculateObjectTransformation() {
    objTransformation = objTranslate.Multiply(objScale).Multiply(objRotateX).Multiply(objRotateY).Multiply(objRotateZ);
    objMatrixDirty = false;
    return objTransformation;
}


/************
 * Calculates object inverse transformation matrix
 ************/
Matrix
DGL::calculateObjectInverseTransformation() {
    return objInverseTransformation;
}

