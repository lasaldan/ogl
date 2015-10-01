//
//  Transformation.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Transformation.h"

Transformation::Transformation(){
    scale = Matrix::Identity();
    translate = Matrix::Identity();
    rotateX = Matrix::Identity();
    rotateY = Matrix::Identity();
    rotateZ = Matrix::Identity();
}

Matrix Transformation::Translate(float x, float y, float z){
    translate.Set(0, 3, x);
    translate.Set(1, 3, y);
    translate.Set(2, 3, z);
    
    CalculateTransformation();
    return translate;
}

Matrix Transformation::RotateX(float deg){
    rotateX.Set(1, 1, cos((PI*deg)/180));
    rotateX.Set(1, 2, sin((PI*deg)/180));
    rotateX.Set(2, 1, -sin((PI*deg)/180));
    rotateX.Set(2, 2, cos((PI*deg)/180));
    
    CalculateTransformation();
    return rotateX;
}
Matrix Transformation::RotateY(float deg) {
    rotateY.Set(0, 0, cos((PI*deg)/180));
    rotateY.Set(0, 2, -sin((PI*deg)/180));
    rotateY.Set(2, 0, sin((PI*deg)/180));
    rotateY.Set(2, 2, cos((PI*deg)/180));
    
    CalculateTransformation();
    return rotateY;
}
Matrix Transformation::RotateZ(float deg) {
    rotateZ.Set(0, 0, cos((PI*deg)/180));
    rotateZ.Set(0, 1, sin((PI*deg)/180));
    rotateZ.Set(1, 0, -sin((PI*deg)/180));
    rotateZ.Set(1, 1, cos((PI*deg)/180));
    
    CalculateTransformation();
    return rotateZ;
    
}
Matrix Transformation::Scale(float s){
    scale.Set(0, 0, s);
    scale.Set(1, 1, s);
    scale.Set(2, 2, s);
    
    CalculateTransformation();
    return scale;
}

Matrix Transformation::CalculateTransformation() {
    //transformationMatrix = rotateX.Multiply(rotateY).Multiply(rotateZ).Multiply(scale).Multiply(translate);
    transformationMatrix = translate.Multiply(scale).Multiply(rotateX).Multiply(rotateY).Multiply(rotateZ);
    return transformationMatrix;
}

Vertex Transformation::Transform(Vertex v) {
    return transformationMatrix.Transform(v);
}