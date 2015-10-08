//
//  main.cpp
//  Southeaster-Competition-2015-2016
//
//  Created by James Landess on 10/7/15.
//  Copyright (c) 2015 James Landess. All rights reserved.
//

#include <iostream>
#include "Timer.h"
int main(int argc, const char * argv[])
{
    PDP::DataStructures::Timer timer;
    
    timer.start();
    
    for (int n = 0; n<1000000; ++n )
    {
        
    }
    
    timer.stop();
    
    std::cout << timer.getElapsedTime() << std::endl;
    return 0;
}
