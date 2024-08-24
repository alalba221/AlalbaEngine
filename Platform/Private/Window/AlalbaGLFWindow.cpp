//
// Created by xinhu on 2024/8/23.
//
#include "Window/AlalbaGLFWindow.h"
#include "AlalbaLog.h"
#include "GLFW/glfw3native.h"
namespace Alalba
{
    AlalbaGLFWindow::AlalbaGLFWindow(uint32_t width, uint32_t height, const char* title)
    {
        if(glfwInit() != GLFW_TRUE)
        {
            LOG_E("Failed to initialize GLFW");
            return;
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);;
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        m_GLFWwindow = glfwCreateWindow(width,height,title, nullptr,nullptr);
        if(!m_GLFWwindow)
        {
            LOG_E("Failed to create GLFW window");
            return;
        }

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        if(primaryMonitor)
        {
            int xPos, yPos, workWidth, workHeight;
            glfwGetMonitorWorkarea(primaryMonitor, &xPos, &yPos, &workWidth, &workHeight);
            glfwSetWindowPos(m_GLFWwindow,workWidth/2-width/2,workHeight/2-height/2);
        }
        glfwMakeContextCurrent(m_GLFWwindow);
        glfwShowWindow(m_GLFWwindow);
    }

    void AlalbaGLFWindow::SwapBuffers()
    {
        glfwSwapBuffers(m_GLFWwindow);
    }

    void AlalbaGLFWindow::PollEvents()
    {
        glfwPollEvents();
    }

    bool AlalbaGLFWindow::ShouldClose()
    {
        return glfwWindowShouldClose(m_GLFWwindow);
    }

    AlalbaGLFWindow::~AlalbaGLFWindow()
    {
        glfwDestroyWindow(m_GLFWwindow);
        glfwTerminate();
        LOG_I("GLFW window destroyed");
    }
}
