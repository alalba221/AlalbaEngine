
#ifndef ALALBAGLFWINDOW_H
#define ALALBAGLFWINDOW_H
#include "AlalbaWindow.h"
#include "GLFW/glfw3.h"
namespace Alalba
{
    class AlalbaGLFWindow : public AlalbaWindow
    {
    public:
        AlalbaGLFWindow() = delete;
        AlalbaGLFWindow(uint32_t width, uint32_t height, const char* title);
        virtual ~AlalbaGLFWindow() override;
    private:
        GLFWwindow* m_GLFWwindow;

    public:
        void SwapBuffers() override;
        void PollEvents() override;
        bool ShouldClose() override;
    };
}
#endif //ALALBAGLFWINDOW_H
