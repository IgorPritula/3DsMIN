//
//  functions.cpp
//  3dViewr
//
//  Created by Igor Prytula on 12/30/18.
//  Copyright © 2018 Ihor Prytula. All rights reserved.
//
#include <ctime>
#include <iostream>

#include "functions.hpp"

void showFps() {
    // Init static veriables
    static int count = 0;
    static std::time_t old_t = std::time(0);
    static std::time_t new_t = std::time(0);
    
    count++;
    new_t = std::time(0);
    if (old_t < new_t) {
        old_t = std::time(0);
        std::cout << "FPS: " << count << std::endl;
        count = 0;
    }
}
