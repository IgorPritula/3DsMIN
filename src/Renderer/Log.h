#ifndef INC_3DSMIN_LOG_H
#define INC_3DSMIN_LOG_H

#ifdef DM_DEBUG_MOD
    #ifdef _WIN32
        #define ASSERT(x) if (!x) __debugbreak()
    #else
        #define ASSERT(x) if (!x) __asm__("int $3")
    #endif

    #define DM_LOG(x) Logger(x, __FILE__, __LINE__);
#else
    #define ASSERT(x)
    #define DM_LOG(x)
#endif
#define GLCall(x) GLClearError(); \
x; \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char*, const char*, int);

void Logger(const char*, const char*, int);

#endif //INC_3DSMIN_LOG_H
