#pragma once

#include "Video/API/API.h"
#include "Video/Renderable2D.hpp"
#include <vector>

#include "Log.h"

#include "Common.h"

namespace tewi
{
    /** \brief A generic 2D renderer.
     *
     * A policy-based class that allows us to render stuff to the screen.
     *
     * \tparam APIType The API you want to use.
     * \tparam RenderPolicy The policy that you want to use to render to the
     * screen.
     *
     * \warning API **and** ABI instability: Inferface may change once Vulkan
     * support is stable enough.
     */
    template <typename APIType,
             template <typename> class RenderPolicy>
    class TEWI_EXPORT Renderer2D final
        : public RenderPolicy<APIType>
    {
        using RenderPolicyImpl = RenderPolicy<APIType>;
    public:
        Renderer2D(ShaderProgram<APIType> shader = RenderPolicyImpl::createShaderProgram())
        {
            
        }

        ~Renderer2D() = default;

        Renderer2D(const Renderer2D& rhs) = delete;
        Renderer2D& operator=(const Renderer2D& rhs) = default;

        Renderer2D(Renderer2D&& rhs) =  delete;
        Renderer2D& operator=(Renderer2D&& rhs) = default;

        /** Begins the rendering by binding the buffers.
         *
         * That's the first function you need to call.
         *
         */
        void begin()
        {
            RenderPolicyImpl::begin();
        }

        /** Add a **single** renderables to the buffer.
         * 
         * Example:
         *
         * \code
         * // Assuming a Renderer named "renderer"
         * // Also assuming a Sprite named "spr"
         *
         * renderer.add(spr.getRenderable());
         *
         * // Or, if the Sprite supports implicit conversion to a Renderable2D
         *
         * renderer.add(spr);
         *
         * \endcode
         *
         * \pre You must call this function after \a begin() and before \a end().
         */
        template <typename T>
        void add(const Renderable2D<T>& renderable)
        {
            static_assert(tewi::is_api_compatible_v<APIType, T>,
                        "You're passing a renderable with an"
                        "API that is neither the same as the renderer's"
                        "nor derived from it.");
            RenderPolicyImpl::add(renderable);
        }

        /** Add a **vector** of renderables to the buffer.
         *
         * Example:
         *
         * \code
         *
         * // Assuming a Renderer named "renderer"
         * // And assuming a std::vector of Renderable2Ds named "vec"
         *
         * renderer.add(vec);
         *
         * \endcode
         *
         * \pre You must call this function after \a begin() and before \a end().
         */
        template <typename Container, typename T = typename Container::value_type::api_type>
        void add(const Container& renderables)
        {
            static_assert(tewi::is_api_compatible_v<APIType, T>,
                        "You're passing a collection of renderables with an"
                        "API that is neither the same as the renderer's"
                        "nor derived from it.");
            RenderPolicyImpl::add(renderables);
        }

        /** Unbinds the buffers.
         *
         * \pre Call this after adding the renderables with \a add() and before \a draw().
         *
         */
        void end()
        {
            RenderPolicyImpl::end();
        }

        /** Does the draw call and resets the buffer.
         *
         * This is the last function you need to call.
         *
         * \pre Call this **after** \a end().
         *
         */
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
