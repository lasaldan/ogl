//
//  vertex.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/15/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include "Vertex.h"
using namespace std;

Vertex::Vertex ( float X, float Y, float Z ) {
    x = X;
    y = Y;
    z = Z;
};

float Vertex::getX() {
    return x;
}

float Vertex::getY() {
    return y;
}

float Vertex::getZ() {
    return z;
}

string Vertex::print() {
    ostringstream ss;
    ss << "Ver: [" << x << "," << y << "," << z << "]";
    return ss.str();
}