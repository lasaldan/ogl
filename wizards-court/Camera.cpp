//
//  Camera.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Camera.h"
#include <math.h>
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
    
    RebuildMatrix();
    */
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
    return;
}

void Camera::lookVertical(float) {
    
}
void Camera::lookHorizonal(float) {
    
}
void Camera::moveHorizontal(float) {
    
}
void Camera::moveForward(float) {
    
}
void Camera::moveVertical(float) {
    
}

void Camera::calculateViewportEquivalent(Vertex) {
    
}