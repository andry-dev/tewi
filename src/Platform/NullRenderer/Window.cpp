#include "tewi/Common.h"
#include "tewi/Video/API/API.h"

#include "tewi/Video/API/Context.hpp"
#include "tewi/Video/Window.hpp"

#include "tewi/Utils/Types.h"

namespace tewi
{
    template <>
    struct TEWI_EXPORT Window<API::NullRendererTag>
    {
      public:
        Window(asl::string_view, Width, Height, void*) {}

        ~Window() = default;
        Window(const Window& rhs) = delete;
        Window& operator=(const Window& rhs) = delete;

        Window(Window&& rhs) = default;
        Window& operator=(Window&& rhs) = default;

        API::Context<API::NullRendererTag> context;
        bool windowClosed = false;
    };

} // namespace tewi
