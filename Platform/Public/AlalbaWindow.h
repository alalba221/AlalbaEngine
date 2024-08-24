
#ifndef ALALBAWINDOW_H
#define ALALBAWINDOW_H
#include "AlalbaEngine.h"

namespace Alalba
{
    class AlalbaWindow
    {
    public:
        AlalbaWindow(const AlalbaWindow&) = delete;
        AlalbaWindow &operator=(const AlalbaWindow&) = delete;
        virtual ~AlalbaWindow() = default;

        static std::unique_ptr<AlalbaWindow> Create(uint32_t width, uint32_t height, const char* title);

        virtual void SwapBuffers() = 0;
        virtual void PollEvents() = 0;
        virtual bool ShouldClose() = 0;

    protected:
        AlalbaWindow() = default;
    };
}


#endif //ALALBAWINDOW_H
