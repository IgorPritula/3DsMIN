#include "Application.h"

#ifdef _WIN32
#include <windows.h>
// Use the High Performance Graphics.
extern "C" {
_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main(int argc, char* argv[]) {

    Application app;
    return app.Run();
}
