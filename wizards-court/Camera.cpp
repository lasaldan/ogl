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

    lookFrom = vector<float> { 0, 5, 40 };
    //lookFrom[0] = 0; lookFrom[1] = 2; lookFrom[2] = 15;
    
    lookAt = vector<float>(3);
    lookAt[0] = 0; lookAt[1] = 2; lookAt[2] = 0;
    
    up = vector<float>(3);
    up[0] = 0; up[1] = 1; up[2] = 0;
    
    //lookHorizontal(10);

    
    translation = Matrix::Identity();
    changeOfBase = Matrix::Identity();
    viewMatrix = Matrix::Identity();
    perspective = Matrix::Identity();
    /*
    float fov = 90;
    float aspect = 4.0f/3.0f;
    float zfar = 1000;
    float znear = 0.001;
    
    perspective.Set(0,0,(1/tan(fov/2))/aspect);
    perspective.Set(1,1,1/tan(fov/2));
    perspective.Set(2,2,(-zfar+znear)/(zfar-znear));
    perspective.Set(2,3,-(2*zfar*znear)/(zfar-znear));
    perspective.Set(3,2,-1);
    */
    // Using matrix from: http://www.songho.ca/opengl/gl_projectionmatrix.html
    
    far = 100;
    near = .1f;
    left = -.01;
    right = .01;
    top = .01;
    bottom = -.01;
    
    
    perspective.Set(0,0, (2 * near) / (right - left));
    perspective.Set(0,2, (right + left) / (right - left));
    
    perspective.Set(1,1, (2 * near) / (top - bottom));
    perspective.Set(1,2, (top + bottom) / (top - bottom));
    
    perspective.Set(2,2, -(far+near)/(far-near));
    perspective.Set(2,3, (-2*far*near)/(far-near));
    
    perspective.Set(3,2,-1);
    perspective.Set(3,3,0);
    
    /*
    perspective.Set(0,0,near/right);
    perspective.Set(1,1,near/top);
    
    perspective.Set(2,2, -(far+near)/(far-near));
    perspective.Set(2,3, (-2*far*near)/(far-near));
    
    perspective.Set(3,2,-1);
    perspective.Set(3,3,0);
    */
    RebuildMatrix();
    
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
    vector <float> temp = vector<float>(3);
    float length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    temp[0] = v[0] / length;
    temp[1] = v[1] / length;
    temp[2] = v[2] / length;
    return temp;
}

void Camera::RebuildMatrix() {

    //lookFrom = {5,-5,8};
    //lookAt = {3,4,0};
    //up = {0,0,1};
    
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
    float t = 0;
}

void Camera::lookHorizontal(float degree) {
    cout << lookFrom[0] << " " <<lookFrom[1] << " " << lookFrom[2] << endl;
    float angle = (degree) * (PI/180); // Convert to radians
    lookAt[0] = cos(angle) * (lookAt[0] - lookFrom[0]) - sin(angle) * (lookAt[2] - lookFrom[2]) + lookFrom[0];
    lookAt[2] = sin(angle) * (lookAt[0] - lookFrom[0]) + cos(angle) * (lookAt[2] - lookFrom[2]) + lookFrom[2];
    RebuildMatrix();
    
}
void Camera::lookVertical(float degree) {
    
    float angle = (degree) * (PI/180); // Convert to radians
    lookAt[1] = cos(angle) * (lookAt[1] - lookFrom[1]) - sin(angle) * (lookAt[2] - lookFrom[2]) + lookFrom[1];
    lookAt[2] = sin(angle) * (lookAt[1] - lookFrom[1]) + cos(angle) * (lookAt[2] - lookFrom[2]) + lookFrom[2];
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
    
    return Vertex(xx, yy, zz);
}