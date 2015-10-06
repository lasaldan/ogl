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
    angle = 0;
    /*
    lookFrom = vector<float>(3);
    lookFrom[0] = 2; lookFrom[1] = 0; lookFrom[2] = 2;
    
    lookAt = vector<float>(3);
    lookAt[0] = 1; lookAt[1] = 0; lookAt[2] = 1;
    
    up = vector<float>(3);
    up[0] = 0; up[1] = 1; up[2] = 0;
    
    
    far = 1000;
    near = .01;
    left = -10;
    right = 10;
    top = 10;
    bottom = -10;
    fov = 45;
     
     */
    lookFrom = vector<float>(3);
    lookFrom[0] = -0; lookFrom[1] = -5; lookFrom[2] = -20;
    
    lookAt = vector<float>(3);
    lookAt[0] = 0; lookAt[1] = 0; lookAt[2] = -2;
    
    up = vector<float>(3);
    up[0] = 0; up[1] = 100; up[2] = 0;
    
    translation = Matrix::Identity();
    changeOfBase = Matrix::Identity();
    viewMatrix = Matrix::Identity();
    perspective = Matrix::Identity();
    
    //perspective.Set(2,2,0);
    //perspective.Set(3,2,-1/400);
    
    
    /*
    perspective.Set(0,0,atan(fov));
    perspective.Set(1,1,atan(fov));
    
    perspective.Set(2,2,-1*((far+near)/(far-near)));
    perspective.Set(2,3,(-1*(2*near*far)/(far-near)));
    
    perspective.Set(3,2,-1);
    perspective.Set(3,3,0);
    
    
    float aspect = (right-left)/(top-bottom);
    float rad = PI / 180.0;
    float yScale = 1.0 / tan(rad * fov / 2);
    float xScale = yScale / aspect;
    float nearmfar = near - far;

    perspective.Set(0,0, xScale);
    
    perspective.Set(1,1, yScale);
    
    perspective.Set(2,2, (far + near) / nearmfar);
    perspective.Set(2,3, -1);
    
    perspective.Set(3,2,2*far*near / nearmfar);
    perspective.Set(3,3,0);
    
    
   */
    
    // Using matrix from: http://www.songho.ca/opengl/gl_projectionmatrix.html
     
    far = 2000;
    near = 1.0f;
    left = -1;
    right = 1;
    top = 1;
    bottom = -1;
    
    perspective.Set(0,0, (2 * near) / (right - left));
    perspective.Set(0,2, (right + left) / (right - left));
    
    perspective.Set(1,1, (2 * near) / (top - bottom));
    perspective.Set(1,2, (top + bottom) / (top - bottom));
    
    perspective.Set(2,2, -(far+near)/(far-near));
    perspective.Set(2,3, (-2*far*near)/(far-near));
    
    perspective.Set(3,2,-1);
    perspective.Set(3,3,1);
    
    RebuildMatrix();
    
    //transform(Vertex(126,126,-320));
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
    
}

void Camera::lookVertical(float) {
    
}
void Camera::lookHorizontal(float amount) {
    
    // Convert global coordinate to local camera space
    Vertex localFacing = WorldToView(lookAt);
    
    Matrix rotation = Matrix::Identity();
    
    rotation.Set(0, 0, cos((PI*amount)/180));
    rotation.Set(0, 2, -sin((PI*amount)/180));
    rotation.Set(2, 0, sin((PI*amount)/180));
    rotation.Set(2, 2, cos((PI*amount)/180));
    
    localFacing = rotation.Transform(localFacing);
    lookAt[0] = localFacing.x;
    lookAt[1] = localFacing.y;
    lookAt[2] = localFacing.z;
    RebuildMatrix();
}

void Camera::moveHorizontal(float distance) {
    lookFrom[0] += distance;
    lookAt[0] += distance;
    RebuildMatrix();
}

void Camera::moveForward(float distance) {
    lookFrom[2] += distance;
    lookAt[2] += distance;
    RebuildMatrix();
}

void Camera::moveVertical(float distance) {
    lookFrom[1] += distance;
}

Vertex Camera::WorldToView(Vertex v) {
    
    // Shift point to new position, based on camera position
    float x =   (viewMatrix.Get(0,0) * v.getX() +
                viewMatrix.Get(0,1) * v.getY() +
                viewMatrix.Get(0,2) * v.getZ() +
                viewMatrix.Get(0,3));
    
    float y =   (viewMatrix.Get(1,0) * v.getX() +
                viewMatrix.Get(1,1) * v.getY() +
                viewMatrix.Get(1,2) * v.getZ() +
                viewMatrix.Get(1,3));
                 
    float z =   (viewMatrix.Get(2,0) * v.getX() +
                viewMatrix.Get(2,1) * v.getY() +
                viewMatrix.Get(2,2) * v.getZ() +
                viewMatrix.Get(2,3));

    // Shift point to new position, based on perspective
    /*
    float w =   (perspective.Get(3,0) * x +
                perspective.Get(3,1) * y +
                perspective.Get(3,2) * z +
                perspective.Get(3,3));
    
    float xx =   (perspective.Get(0,0) * x +
                 perspective.Get(0,1) * y +
                 perspective.Get(0,2) * z +
                 perspective.Get(0,3)) / w;
    
    float yy =   (perspective.Get(1,0) * x +
                 perspective.Get(1,1) * y +
                 perspective.Get(1,2) * z +
                 perspective.Get(1,3)) / w;
    
    float zz =   (perspective.Get(2,0) * x +
                 perspective.Get(2,1) * y +
                 perspective.Get(2,2) * z +
                 perspective.Get(2,3)) / w;
    */
    return Vertex(x, y, z/30);
}