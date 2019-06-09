#include "tewi/Video/API/Context.hpp"

namespace tewi
{
    namespace API
    {
        template <>
        class TEWI_EXPORT Context<API::NullRendererTag> final
        {
        public:
            Context() {}
            void setup() {}
            void postInit(GLFWwindow*) {}
            void preDraw() {}
            void postDraw() {}
            void swap(GLFWwindow*) {}
            const auto getAPIVersion()
            {
                return "Null Renderer";
            }
        };
    } // namespace API
} // namespace tewi
