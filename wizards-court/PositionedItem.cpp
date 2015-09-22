//
//  PositionedItem.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "PositionedItem.h"

PositionedItem::PositionedItem(Item i) {
    x = 0;
    y = 0;
    z = 0;
    rotation = 0;
    item = i;
}

Item PositionedItem::GetItem() {
    return item;
}