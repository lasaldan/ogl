//
//  PositionedItem.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "PositionedItem.h"

PositionedItem::PositionedItem(Item i) {
    matrix = Transformation();
    item = i;
}

Item PositionedItem::GetItem() {
    return item;
}

Transformation& PositionedItem::GetMatrix() {
    return matrix;
}

PositionedItem& PositionedItem::Translate(float x, float y, float z) {
    matrix.Translate(x, y, z);
    return *this;
}

PositionedItem& PositionedItem::RotateX(float deg) {
    matrix.RotateX(deg);
    return *this;
}
PositionedItem& PositionedItem::RotateY(float deg) {
    matrix.RotateY(deg);
    return *this;
}
PositionedItem& PositionedItem::RotateZ(float deg) {
    matrix.RotateZ(deg);
    return *this;
}
PositionedItem& PositionedItem::Scale(float s) {
    matrix.Scale(s);
    return *this;
}

Vertex PositionedItem::LocalToWorld(Vertex v) {
    return matrix.LocalToWorld(v);
}