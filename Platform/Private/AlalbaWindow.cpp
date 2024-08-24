#include "AlalbaWindow.h"
#include "Window/AlalbaGLFWindow.h"
namespace Alalba
{
    std::unique_ptr<AlalbaWindow> AlalbaWindow::Create(uint32_t width, uint32_t height, const char* title)
    {
#ifdef ALALBA_ENGINE_PLATFORM_WIN32
        //Windows
        return std::make_unique<AlalbaGLFWindow>(width, height, title);
#elif ALALBA_ENGINE_PLATFORM_MACOS
        //Macos
        return std::make_unique<AlalbaGLFWindow>(width, height, title);
#elif ALALBA_ENGINE_PLATFORM_LINUX
        // Linux
        return std::make_unique<AlalbaGLFWindow>(width, height, title);
#endif

    }
}
