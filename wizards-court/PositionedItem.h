//
//  PositionedItem.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__PositionedItem__
#define __wizards_court__PositionedItem__

#include <stdio.h>
#include "Item.h"
#include "Transformation.h"

class PositionedItem {
private:
    Transformation matrix;
    Item item;
public:
    PositionedItem(Item);
    Item GetItem();
    Transformation& GetMatrix();
    PositionedItem& Translate(float x, float y, float z);
    PositionedItem& Scale(float x);
    PositionedItem& RotateX(float deg);
    PositionedItem& RotateY(float deg);
    PositionedItem& RotateZ(float deg);
    Vertex LocalToWorld(Vertex);
};

#endif /* defined(__wizards_court__PositionedItem__) */
