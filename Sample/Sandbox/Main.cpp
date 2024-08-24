#include <iostream>
#include "AlalbaLog.h"
#include "AlalbaWindow.h"
int main()
{
    std::cout << "Hello Alalba engine." << std::endl;
    Alalba::AlalbaLog::Init();
    LOG_E("hello spdlog: {0},{1},{3}",__FUNCTION__, 1,0.14f,true);
    LOG_I("hello spdlog: {0},{1},{3}",__FUNCTION__, 1,0.14f,true);
    LOG_W("hello spdlog: {0},{1},{3}",__FUNCTION__, 1,0.14f,true);
    LOG_D("hello spdlog: {0},{1},{3}",__FUNCTION__, 1,0.14f,true);

    std::unique_ptr<Alalba::AlalbaWindow> window = Alalba::AlalbaWindow::Create(800,600,"Sandbox");
    while(!window->ShouldClose())
    {
        window->PollEvents();
        window->SwapBuffers();
    };

    return EXIT_SUCCESS;
}