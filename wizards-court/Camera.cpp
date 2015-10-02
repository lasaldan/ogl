//
//  Camera.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Camera.h"
#include <math.h>
#include <iostream>
using namespace std;

Camera::Camera() {
    //glTranslatef(0.0f, -1.0f, -2.0f); // Local: +l/-r , -u/+d , +f/-b
    //glRotatef(0, 0.0f, 1.0f, 0.0f);
    /*
    lookFrom = vector<float>(3);
    lookFrom[0] = 2; lookFrom[1] = 0; lookFrom[2] = 2;
    
    lookAt = vector<float>(3);
    lookAt[0] = 1; lookAt[1] = 0; lookAt[2] = 1;
    
    up = vector<float>(3);
    up[0] = 0; up[1] = 1; up[2] = 0;
    */
    
    lookFrom = vector<float>(3);
    lookFrom[0] = 0; lookFrom[1] = 4; lookFrom[2] = 10;
    
    lookAt = vector<float>(3);
    lookAt[0] = 0; lookAt[1] = 0; lookAt[2] = 1;
    
    up = vector<float>(3);
    up[0] = 0; up[1] = 100; up[2] = 0;
   
    
    translation = Matrix::Identity();
    changeOfBase = Matrix::Identity();
    viewMatrix = Matrix::Identity();
    perspective = Matrix::Identity();
    
    RebuildMatrix();
    transform(Vertex(-1,1,0));
}

void Camera::setFromLocation(vector<float> loc) {
    lookFrom = loc;
}
void Camera::setLookLocation(vector<float> at) {
    lookAt = at;
}
void Camera::setUp(vector<float> u) {
    up = u;
}

vector<float> Camera::Cross(vector<float> left, vector<float> right) {
    vector<float> temp = vector<float>(3);
    temp[0] = left[1]*right[2] - left[2]*right[1];
    temp[1] = left[2]*right[0] - left[0]*right[2];
    temp[2] = left[0]*right[1] - left[1]*right[0];
    return temp;
}

vector<float> Camera::Minus(vector<float> left, vector<float> right) {
    vector<float> temp = vector<float>(3);
    temp[0] = left[0] - right[0];
    temp[1] = left[1] - right[1];
    temp[2] = left[2] - right[2];
    return temp;
}

vector<float> Camera::Normalize(vector<float> v) {
    float length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] = v[0] / length;
    v[1] = v[1] / length;
    v[2] = v[2] / length;
    return v;
}

void Camera::RebuildMatrix() {
    N = Normalize(Minus(lookFrom, lookAt));
    U = Normalize(Cross(up,N));
    V = Normalize(Cross(N,U));
    
    translation.Set(0,3,-lookAt[0]);
    translation.Set(1,3,-lookAt[1]);
    translation.Set(2,3,-lookAt[2]);
    
    changeOfBase.Set(0,0,U[0]);
    changeOfBase.Set(0,1,U[1]);
    changeOfBase.Set(0,2,U[2]);
    changeOfBase.Set(1,0,V[0]);
    changeOfBase.Set(1,1,V[1]);
    changeOfBase.Set(1,2,V[2]);
    changeOfBase.Set(2,0,N[0]);
    changeOfBase.Set(2,1,N[1]);
    changeOfBase.Set(2,2,N[2]);
    
    viewMatrix = changeOfBase.Multiply(translation);
    
    perspective.Set(2,2,0);
    perspective.Set(3,2,-1/fabs(viewMatrix.Get(2,3)));

    return;
}

void Camera::lookVertical(float) {
    
}
void Camera::lookHorizonal(float) {
    
}
void Camera::moveHorizontal(float) {
    lookFrom[2] += 0.05;
    RebuildMatrix();

}
void Camera::moveForward(float) {
    
}
void Camera::moveVertical(float) {
    
}

Vertex Camera::transform(Vertex v) {
    float x = viewMatrix.Get(0,0) * v.getX() + viewMatrix.Get(0,1) *v.getY() + viewMatrix.Get(0,2) * v.getZ() + viewMatrix.Get(0,3);
    float y = viewMatrix.Get(1,0) * v.getX() + viewMatrix.Get(1,1) *v.getY() + viewMatrix.Get(1,2) * v.getZ() + viewMatrix.Get(1,3);
    float z = viewMatrix.Get(2,0) * v.getX() + viewMatrix.Get(2,1) *v.getY() + viewMatrix.Get(2,2) * v.getZ() + viewMatrix.Get(2,3);
    
    float xx = perspective.Get(0,0) * x + perspective.Get(0,1) * y + perspective.Get(0,2) * z + perspective.Get(0,3);
    float yy = perspective.Get(1,0) * x + perspective.Get(1,1) * y + perspective.Get(1,2) * z + perspective.Get(1,3);
    float zz = perspective.Get(3,2);
    float divisor = zz * z + 1;
    
    return Vertex(xx / divisor,yy / divisor, 0);
}