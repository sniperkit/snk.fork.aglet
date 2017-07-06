#include "aglet/GLContext.h"

#include <assert.h>

// clang-format off
#if defined(AGLET_HAS_GLFW)
#  include "aglet/GLFWContext.h"
#endif
// clang-format on

// clang-format off
#if defined(AGLET_IOS)
#  include "aglet/GLContextIOS.h"
#endif
// clang-format on

// clang-format off
#if defined(AGLET_ANDROID)
#  include "aglet/GLContextAndroid.h"
#endif
// clang-format on

#include <memory>

AGLET_BEGIN

auto GLContext::create(ContextKind kind, const std::string& name, int width, int height) -> GLContextPtr
{
    switch (kind)
    {
        case kAuto:

#if defined(AGLET_IOS)
        case kIOS:
            return std::make_shared<aglet::GLContextIOS>();
#endif

#if defined(AGLET_ANDROID)
        case kAndroid:
            return std::make_shared<aglet::GLContextAndroid>();
#endif

#if defined(AGLET_HAS_GLFW)
        case kGLFW:
            return std::make_shared<aglet::GLFWContext>(name, width, height);
#endif

        default:
            assert(false);
            break;
    }

    return nullptr;
}

AGLET_END