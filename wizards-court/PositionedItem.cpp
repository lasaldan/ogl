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