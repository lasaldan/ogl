//
//  PositionedItem.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "PositionedItem.h"

PositionedItem::PositionedItem(Item i) {
    matrix = TransformationMatrix();
    item = i;
}

Item PositionedItem::GetItem() {
    return item;
}

TransformationMatrix& PositionedItem::GetMatrix() {
    return matrix;
}

void PositionedItem::Translate(float x, float y, float z) {
    matrix.Translate(x, y, z);
}

void PositionedItem::RotateX(float deg) {
    matrix.RotateX(deg);
}
void PositionedItem::RotateY(float deg) {
    matrix.RotateY(deg);
}
void PositionedItem::RotateZ(float deg) {
    matrix.RotateZ(deg);
}
void PositionedItem::Scale(float s) {
    matrix.Scale(s);
}