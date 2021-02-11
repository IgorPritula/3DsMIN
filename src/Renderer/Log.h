#ifndef INC_3DSMIN_LOG_H
#define INC_3DSMIN_LOG_H

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

#endif //INC_3DSMIN_LOG_H
