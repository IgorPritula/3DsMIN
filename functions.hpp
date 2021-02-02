//
//  Copyright © 2021 Ihor Prytula.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>

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
void DEBUG_run_as_macos_app();
#endif /* functions_hpp */
