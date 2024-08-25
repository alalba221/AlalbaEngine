#include "AlalbaGFXContext.h"
#include "GFX/Vulkan/GFXContext.h"
namespace Alalba
{
  std::unique_ptr<AlalbaGFXContext> AlalbaGFXContext::Create(AlalbaWindow *window)
  {
#ifdef ALALBA_ENGINE_GRAPHIC_API_VULKAN
    return std::make_unique<vk::GFXContext>(window);
#else

#endif
    return nullptr;
  }
}
