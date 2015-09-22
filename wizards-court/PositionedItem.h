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

class PositionedItem {
private:
    float x;
    float y;
    float z;
    float rotation;
    Item item;
public:
    PositionedItem(Item);
    Item GetItem();
};

#endif /* defined(__wizards_court__PositionedItem__) */
