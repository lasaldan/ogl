//
//  ManifestParser.h
//  wizards-court
//
//  Created by Daniel Fuller on 9/23/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#ifndef __wizards_court__ManifestParser__
#define __wizards_court__ManifestParser__

#include <stdio.h>
#include <iostream>

class ManifestParser{
    
    ManifestParser();
    void parseFile(std::string path, Item* i);
    void parseItem(string line);
    
};

#endif /* defined(__wizards_court__ManifestParser__) */
