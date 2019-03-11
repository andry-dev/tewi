#include "tewi/Video/BatchRenderer2D.hpp"
#include "tewi/Video/API/API.h"

namespace tewi
{
    template <>
    struct TEWI_EXPORT BatchRenderer2D<API::NullRendererTag>
    {
    protected:
        BatchRenderer2D() = default;
        BatchRenderer2D(const BatchRenderer2D& rhs) = delete;
        BatchRenderer2D& operator=(const BatchRenderer2D& rhs) = delete;

        BatchRenderer2D(BatchRenderer2D&& rhs) = default;
        BatchRenderer2D& operator=(BatchRenderer2D&& rhs) = default;

        void begin() {}

        template <typename T>
        void add(const Renderable2D<T>& renderable) {}

        template <typename Container>
        void add(const Container& renderableList) {}

        void end() {}

        void draw() {}

        static ShaderProgram<API::NullRendererTag> createShaderProgram()
        {
            return ShaderProgram<API::NullRendererTag>{ { }, { } };
        }
    };
} // namespace tewi
