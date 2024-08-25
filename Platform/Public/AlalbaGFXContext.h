
#ifndef ALALBAGFXCONTEXT_H
#define ALALBAGFXCONTEXT_H
#include "AlalbaEngine.h"
namespace Alalba
{
    class AlalbaWindow;
    class AlalbaGFXContext
    {
    public:
        AlalbaGFXContext(const AlalbaGFXContext&) = delete;
        AlalbaGFXContext &operator=(const AlalbaGFXContext&) = delete;
        virtual ~AlalbaGFXContext() = default;

        static std::unique_ptr<AlalbaGFXContext> Create(AlalbaWindow* window);
    protected:
        AlalbaGFXContext() = default;
    };
}
#endif //ALALBAGFXCONTEXT_H
