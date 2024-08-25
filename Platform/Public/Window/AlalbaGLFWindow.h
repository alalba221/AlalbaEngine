
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


        void SwapBuffers() override;
        void PollEvents() override;
        bool ShouldClose() override;
        GLFWwindow *GetWindowHandle() const { return m_GLFWwindow; }

    private:
        GLFWwindow* m_GLFWwindow;
    };
}
#endif //ALALBAGLFWINDOW_H
