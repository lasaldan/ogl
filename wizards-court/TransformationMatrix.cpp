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

vector< vector< float > > TransformationMatrix::Cross(TransformationMatrix){
    TransformationMatrix temp = TransformationMatrix();
    return matrixData;
}
vector< vector< float > > TransformationMatrix::Dot(TransformationMatrix){
    TransformationMatrix temp = TransformationMatrix();
    return matrixData;
    
}
vector< vector< float > > TransformationMatrix::GetMatrix() {
    return matrixData;
}
vector< vector< float > > TransformationMatrix::Multiply(TransformationMatrix input){
    vector< vector< float > > temp;
    temp.resize(4);
    temp[0].resize(4);
    temp[1].resize(4);
    temp[2].resize(4);
    temp[3].resize(4);
    vector< vector< float > > rightSide = input.GetMatrix();
    // Assume square matrices
    for(int answerRow=0; answerRow < matrixData[0].size(); answerRow ++) {
        for(int answerCol=0; answerCol < matrixData[0].size(); answerCol++) {
            float val = 0;
            for(int valCounter=0; valCounter < matrixData[0].size(); valCounter ++) {
                val += matrixData[answerRow][valCounter] * rightSide[valCounter][answerCol];
            }
            temp[answerRow][answerCol] = val;
        }
    }
    return temp;
}
void TransformationMatrix::Translate(float x, float y, float z){
    TransformationMatrix temp = TransformationMatrix();
    temp.setValue(0, 3, x);
    temp.setValue(1, 3, y);
    temp.setValue(2, 3, z);
    
    matrixData = Multiply(temp);
}
void TransformationMatrix::RotateX(float deg){
    TransformationMatrix temp = TransformationMatrix();
    temp.setValue(1, 1, cos((PI*deg)/180));
    temp.setValue(1, 2, sin((PI*deg)/180));
    temp.setValue(2, 1, -sin((PI*deg)/180));
    temp.setValue(2, 2, cos((PI*deg)/180));
    
    matrixData = Multiply(temp);
}
void TransformationMatrix::RotateY(float deg) {
    TransformationMatrix temp = TransformationMatrix();
    temp.setValue(0, 0, cos((PI*deg)/180));
    temp.setValue(0, 2, -sin((PI*deg)/180));
    temp.setValue(2, 0, sin((PI*deg)/180));
    temp.setValue(2, 2, cos((PI*deg)/180));
    
    matrixData = Multiply(temp);
}
void TransformationMatrix::RotateZ(float deg) {
    TransformationMatrix temp = TransformationMatrix();
    temp.setValue(0, 0, cos((PI*deg)/180));
    temp.setValue(0, 1, sin((PI*deg)/180));
    temp.setValue(1, 0, -sin((PI*deg)/180));
    temp.setValue(1, 1, cos((PI*deg)/180));
    
    matrixData = Multiply(temp);
    
}
void TransformationMatrix::Scale(float s){
    TransformationMatrix temp = TransformationMatrix();
    temp.setValue(0, 0, s);
    temp.setValue(1, 1, s);
    temp.setValue(2, 2, s);
    
    matrixData = Multiply(temp);
}
void TransformationMatrix::setValue(int row, int col, float val) {
    matrixData[row][col] = val;
}
Vertex TransformationMatrix::Transform(Vertex v) {
    float x = matrixData[0][0] * v.getX() + matrixData[0][1] * v.getY() + matrixData[0][2] * v.getZ() + matrixData[0][3];
    float y = matrixData[1][0] * v.getX() + matrixData[1][1] * v.getY() + matrixData[1][2] * v.getZ() + matrixData[1][3];
    float z = matrixData[2][0] * v.getX() + matrixData[2][1] * v.getY() + matrixData[2][2] * v.getZ() + matrixData[2][3];
    Vertex transformedVertex = Vertex(x, y, z);
    return transformedVertex;
}