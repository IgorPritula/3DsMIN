#include "Debug.h"

#ifdef __APPLE__
#include <unistd.h>
#include <mach-o/dyld.h>
#endif

#include <ctime>
#include <iostream>

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

#ifdef __APPLE__
void DEBUG_run_as_macos_app() {
    uint32_t i = 1024;
    char *s;
    s = new char[i];
    _NSGetExecutablePath(s, &i);
    std::string str = std::string(s);
    str = str.substr(0, str.find_last_of("/"));
    std::cout << str << std::endl;
    if (!chdir(str.c_str()))
        std::cout << std::string("Failed to change working directory to executable path: ") + strerror(errno)
                  << std::endl;
    delete[] s;
}
#endif