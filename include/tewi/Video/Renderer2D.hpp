#pragma once

#include <vector>


#include "tewi/Common.h"
#include "tewi/Utils/Log.h"
#include "tewi/Video/API/API.h"
#include "tewi/Video/Shader.hpp"
#include "tewi/Video/Renderable2D.hpp"

namespace tewi
{
    template <typename APIType,
             template <typename> class RenderPolicy>
    class TEWI_EXPORT Renderer2D final
        : public RenderPolicy<APIType>
    {
        using RenderPolicyImpl = RenderPolicy<APIType>;
    public:

        Renderer2D()
            : RenderPolicyImpl()
        { }

        ~Renderer2D() = default;

        Renderer2D(const Renderer2D& rhs) = delete;
        Renderer2D& operator=(const Renderer2D& rhs) = default;

        Renderer2D(Renderer2D&& rhs) =  delete;
        Renderer2D& operator=(Renderer2D&& rhs) = default;

        void begin()
        {
            RenderPolicyImpl::begin();
        }

        template <typename T>
        void add(const Renderable2D<T>& renderable)
        {
            static_assert(tewi::is_api_compatible_v<APIType, T>,
                        "You're passing a renderable with an"
                        "API that is neither the same as the renderer's"
                        "nor derived from it.");
            RenderPolicyImpl::add(renderable);
        }

        template <typename Container, typename T = typename Container::value_type::api_type>
        void add(const Container& renderables)
        {
            static_assert(tewi::is_api_compatible_v<APIType, T>,
                        "You're passing a collection of renderables with an"
                        "API that is neither the same as the renderer's"
                        "nor derived from it.");
            RenderPolicyImpl::add(renderables);
        }

        void end()
        {
            RenderPolicyImpl::end();
        }

        void draw()
        {
            RenderPolicyImpl::draw();
        }

        static ShaderProgram<APIType> createShaderProgram()
        {
            return RenderPolicyImpl::createShaderProgram();
        }
    private:
    };

    /** \example renderer2D_usage.cpp
     *
     * Usage of Renderer2D
     */

} // namespace tewi
