//
//  TransformationMatrix.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "TransformationMatrix.h"

TransformationMatrix::TransformationMatrix(){
    matrixData.resize(4);
    matrixData[0].resize(4);
    matrixData[1].resize(4);
    matrixData[2].resize(4);
    matrixData[3].resize(4);
    
    matrixData[0][0] = 1;
    matrixData[1][1] = 1;
    matrixData[2][2] = 1;
    matrixData[3][3] = 1;
}

TransformationMatrix TransformationMatrix::Cross(TransformationMatrix){
    TransformationMatrix temp = TransformationMatrix();
    return temp;
}
TransformationMatrix TransformationMatrix::Dot(TransformationMatrix){
    TransformationMatrix temp = TransformationMatrix();
    return temp;
    
}
void TransformationMatrix::SetTranslation(Vertex v){
    matrixData[0][3] = v.getX();
    matrixData[1][3] = v.getY();
    matrixData[2][3] = v.getZ();
}
void TransformationMatrix::SetRotation(float x, float y, float z){
    
}
void TransformationMatrix::SetScale(float s){
    matrixData[0][0] = s;
    matrixData[1][1] = s;
    matrixData[2][2] = s;
    
}
void TransformationMatrix::AddTranslation(float x, float y, float z){
    matrixData[0][3] += x;
    matrixData[1][3] += y;
    matrixData[2][3] += z;
}
void TransformationMatrix::AddRotation(float x, float y, float z){
    
}
void TransformationMatrix::AddScale(float s){
    
}
Vertex TransformationMatrix::Transform(Vertex v) {
    float x = matrixData[0][0] * v.getX() + matrixData[0][1] * v.getY() + matrixData[0][2] * v.getZ() + matrixData[0][3];
    float y = matrixData[1][0] * v.getX() + matrixData[1][1] * v.getY() + matrixData[1][2] * v.getZ() + matrixData[1][3];
    float z = matrixData[2][0] * v.getX() + matrixData[2][1] * v.getY() + matrixData[2][2] * v.getZ() + matrixData[2][3];
    Vertex transformedVertex = Vertex(x, y, z);
    return transformedVertex;
}