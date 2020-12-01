//
//  functions.hpp
//  3dViewr
//
//  Created by Igor Prytula on 12/30/18.
//  Copyright © 2018 Ihor Prytula. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>

#define DEF_VIEWPORT_W 1024
#define DEF_VIEWPORT_H 768

// @todo wrap each opengl function in GLCall
#ifdef __APPLE__
#define ASSERT(x) if (!x) __asm__("int $3")
#else
#define ASSERT(x) if (!x) __asm { int 3 }
#endif
#define GLCall(x) GLClearError(); \
x; \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char*, const char*, int);

void showFps();

#endif /* functions_hpp */
