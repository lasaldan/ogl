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
#include "TransformationMatrix.h"

class PositionedItem {
private:
    TransformationMatrix matrix;
    Item item;
public:
    PositionedItem(Item);
    Item GetItem();
    TransformationMatrix& GetMatrix();
};

#endif /* defined(__wizards_court__PositionedItem__) */
