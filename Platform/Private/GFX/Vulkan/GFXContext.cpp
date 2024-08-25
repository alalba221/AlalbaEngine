#include "GFX/Vulkan/GFXContext.h"
#include "Window/AlalbaGLFWindow.h"
namespace vk
{
  const ContextFeature requestedLayers[] =
  {
    { "VK_LAYER_KHRONOS_validation", true },
  };
  const ContextFeature requestedExtensions[] =
  {
    { VK_KHR_SURFACE_EXTENSION_NAME, true },
#ifdef ALALBA_DEBUG
    // { VK_EXT_DEBUG_UTILS_EXTENSION_NAME, true },
    { "VK_EXT_debug_report", true },
#endif

#ifdef ALALBA_ENGINE_PLATFORM_WIN32
    { VK_KHR_WIN32_SURFACE_EXTENSION_NAME, true },
#elif ALALBA_ENGINE_PLATFORM_MACOS
    { VK_MVK_MACOS_SURFACE_EXTENSION_NAME, true },
#elif ALALBA_ENGINE_PLATFORM_LINUX
    { VK_KHR_XCB_SURFACE_EXTENSION_NAME, true },
#endif
  };

  GFXContext::GFXContext(Alalba::AlalbaWindow *window)
  {
    CreateInstance();
    CreateSurface(window);
  }

  GFXContext::~GFXContext()
  {
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    vkDestroyInstance(m_instance, nullptr);
  }
  static VkBool32 VkDebugReportCallback(VkDebugReportFlagsEXT flags,
                VkDebugReportObjectTypeEXT                  objectType,
                uint64_t                                    object,
                size_t                                      location,
                int32_t                                     messageCode,
                const char*                                 pLayerPrefix,
                const char*                                 pMessage,
                void*                                       pUserData)
  {
    if(flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
    {
      LOG_E("{0}", pMessage);
    }
    if(flags & VK_DEBUG_REPORT_WARNING_BIT_EXT || flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT){
      LOG_W("{1}", pMessage);
    }
    return VK_TRUE;
  }
  void GFXContext::CreateInstance()
  {
    // 1, layers
    uint32_t availableLayerCount = 0;
    CALL_VK(vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr));
    std::vector<VkLayerProperties> availableLayers(availableLayerCount);
    CALL_VK(vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers.data()));

    uint32_t enableLayerCount = 0;
    const char* enableLayers[32];
    if(!checkContextFeatures("Instance Layers",false,availableLayerCount,availableLayers.data(),
                          ARRAY_SIZE(requestedLayers),requestedLayers,&enableLayerCount,enableLayers))
    {
      return;
    }

    // 2, extension
    uint32_t availableExtensionCount;
    CALL_VK(vkEnumerateInstanceExtensionProperties("", &availableExtensionCount, nullptr));
    std::vector<VkExtensionProperties> availableExtensions(availableExtensionCount);
    CALL_VK(vkEnumerateInstanceExtensionProperties("", &availableExtensionCount, availableExtensions.data()));

    uint32_t glfwRequestedExtensionCount;
    const char ** glfwRequestedExtensions = glfwGetRequiredInstanceExtensions(&glfwRequestedExtensionCount);
    std::unordered_set<const char*> allRequestedExtensionSet;
    std::vector<ContextFeature> allRequestedExtensions;
    for (const auto &item: requestedExtensions)
    {
      if(allRequestedExtensionSet.find(item.name) == allRequestedExtensionSet.end())
      {
        allRequestedExtensionSet.insert(item.name);
        allRequestedExtensions.push_back(item);
      }
    }
    for (int i = 0; i < glfwRequestedExtensionCount; i++)
    {
      const char *extensionName = glfwRequestedExtensions[i];
      if(allRequestedExtensionSet.find(extensionName) == allRequestedExtensionSet.end())
      {
        allRequestedExtensionSet.insert(extensionName);
        allRequestedExtensions.push_back({ extensionName, true });
      }
    }

    uint32_t enableExtensionCount;
    const char *enableExtensions[32];
    if(!checkContextFeatures("Instance Extension", true, availableExtensionCount, availableExtensions.data(),
                            allRequestedExtensions.size(), allRequestedExtensions.data(), &enableExtensionCount, enableExtensions))
    {
      return;
    }

    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext = nullptr;
    applicationInfo.pApplicationName = "Alalba_Engine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "None";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;


    VkDebugReportCallbackCreateInfoEXT debugReportCallbackInfoExt{};

    debugReportCallbackInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    debugReportCallbackInfoExt.pNext = nullptr;
    debugReportCallbackInfoExt.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT
              | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT
              | VK_DEBUG_REPORT_ERROR_BIT_EXT;
    debugReportCallbackInfoExt.pfnCallback = VkDebugReportCallback;

    // 3. create instance
    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
#ifdef ALALBA_DEBUG
    instanceInfo.pNext = &debugReportCallbackInfoExt;
#else
    instanceInfo.pNext = nullptr;
#endif
    instanceInfo.flags = 0;
    instanceInfo.pApplicationInfo = &applicationInfo;
    instanceInfo.enabledLayerCount = enableLayerCount;
    instanceInfo.ppEnabledLayerNames = enableLayerCount > 0 ? enableLayers : nullptr;
    instanceInfo.enabledExtensionCount = enableExtensionCount;
    instanceInfo.ppEnabledExtensionNames = enableExtensionCount > 0 ? enableExtensions : nullptr;

    CALL_VK(vkCreateInstance(&instanceInfo, nullptr, &m_instance));
    LOG_T("{0} : instance : {1}", __FUNCTION__, (void*)m_instance);
  }

  void GFXContext::CreateSurface(Alalba::AlalbaWindow *window) {
    if(!window){
      LOG_E("window is not exists.");
      return;
    }

    auto *glfWwindow = dynamic_cast<Alalba::AlalbaGLFWindow *>(window);
    if(!glfWwindow){
      // FIXME
      LOG_E("this window is not a glfw window.");
      return;
    }
    CALL_VK(glfwCreateWindowSurface(m_instance, glfWwindow->GetWindowHandle(), nullptr, &m_surface));
    LOG_T("{0} : surface : {1}", __FUNCTION__, (void*)m_surface);
  }
}
