//
//  main.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/12/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "main.h"
#include "Game.h"
using namespace std;


int main (int argc, char **argv)
{
    Game game = Game();
    return game.Run();
}
