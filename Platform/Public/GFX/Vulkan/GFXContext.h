
#ifndef ALALBA_VK_GFXCONTEXT_H
#define ALALBA_VK_GFXCONTEXT_H
#include "AlalbaGFXContext.h"
#include "VKCommon.h"
namespace vk
{
    class GFXContext : public Alalba::AlalbaGFXContext {
    public:
        GFXContext(Alalba::AlalbaWindow* window);
        ~GFXContext() override;

    private:
        void CreateInstance();
        void CreateSurface(Alalba::AlalbaWindow* window);
        VkInstance m_instance;
        VkSurfaceKHR m_surface;
    };
}

#endif //ALALBA_VK_GFXCONTEXT_H
