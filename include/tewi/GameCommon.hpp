#pragma once

#include <memory>

#include "tewi/Common.h"

#include "tewi/IO/InputManager.h"
#include "tewi/Utils/TickTimer.h"
#include "tewi/Utils/GLFWCallbacks.h"

#include "tewi/Video/Window.hpp"
#include "tewi/Video/API/Context.hpp"
#include "tewi/Video/API/Instance.hpp"
#include "tewi/Video/API/Swapchain.hpp"
#include "tewi/Platform/OpenGL/Context.hpp"

#include "tewi/Utils/Log.h"


namespace tewi
{
    /** \brief Managed base game class.
     *
     * Inherit from this class to get a managed base game class.
     *
     * **If this is your first time seeing this engine and you stumbled upon this class then read:**
     *
     * **This class uses a template parameter of type int called *APINum*, use this to switch the used graphic API.**
     *
     * **Possible values are listed in the enum API::API_TYPE.**
     *
     * **This is a common pattern in the engine.**
     *
     * It basically sets up everything for you, so you don't need to lose time writing window creation and game loop management.
     *
     * This class uses the CRTP idiom to statically dispatch the function calls, so you **need to implement every function or your program will seg fault.**
     *
     * Example in your own code:
     *
     * \code
     *
     * #include "GameCommon.hpp"
     *
     * using namespace tewi;
     *
     * class MainGame : public GameCommon<MainGame, API::API_TYPE::OPENGL>
     * {
     * public:
     *    void init();
     *    void processInputs();
     *    void update();
     *    void draw();
     *
     * // Your functions
     * // [...]
     *
     *
     * private:
     *
     * // Your variables
     *
     * };
     *
     * \endcode
     *
     * Then, your code is exposed to the protected members of this class.
     *
     * **Common Questions:**
     *
     *
     * "How do I dynamically dispatch this?"
     *
     * "How do I choose in runtime what API to use?"
     *
     * There is a solution that it's not really pretty.
     *
     * Let's say you create a class named "MainGame" that inherits from this; what you can do is the following:
     *
     * Add a template argument to "MainGame" so that it takes any typename and in main.cpp just branch:
     *
     * \code
     *
     * int main()
     * {
     *     // Let's say this is the runtime result based on which you switch API
     *     bool someEval = ...;
     *
     *     if (someEval)
     *     {
     *         MainGame<tewi::API::OpenGLTag> oglGame;
     *         oglGame.start();
     *     }
     *     else
     *     {
     *         MainGame<tewi::API:VulkanTag> vkGame;
     *         vkGame.start();
     *     }
     *
     *    return 0;
     * }
     *
     * \endcode
     *
     *
     * This works like you'd expect and in fact provides "runtime" dispatch but there are some caveats:
     * * It bloats the size of the executable.
     * * It's not pretty.
     *
     * The main concern is the first, but that's the price I'm paying for not using virtual calls.
     *
     */
    template <class Derived, typename APINum>
    class TEWI_EXPORT GameCommon
    {
    public:

        GameCommon(const std::string& windowName, int width, int height)
            : m_window(std::make_unique<Window<APINum>>(windowName, width, height, this))
            , m_swapchain(m_instance, *m_window)
        {
            Log::info("CALLED GameCommon::GameCommon");

            m_swapchain.secondPhaseInit(m_device);

            m_window->setKeyboardCallback(tewi::glfwKeyboardCallback<Derived, APINum>);
            m_window->setMouseButtonCallback(tewi::glfwMouseCallback<Derived, APINum>);
            m_window->setMouseCursorPosCallback(tewi::glfwCursorPosCallback<Derived, APINum>);
        }

        ~GameCommon()
        {
            Log::info("CALLED GameCommon::~GameCommon");
        }


        /** Basically arbitrarily starts the game.
         *
         * The constructor alone won't do it for you.
         *
         */
        void start()
        {
            run();
        }

    protected:
        /** Initializes the game.
         * 
         * This function is called only once, use it to initialize basic game objects.
         *
         */
        void init()
        {
            impl().init();
        }

        /** Processes inputs through the input manager.
         *
         *
         * It's the first function that is called in a frame.
         */
        void processInputs()
        {
            impl().processInputs();
        }

        /** All your update logic goes here (like physics, camera, etc...).
         *
         * 
         *
         * It's the second function that is called in a frame.
         *
         */
        void update()
        {
            m_window->pollEvents();
            impl().update();
        }

        /** Draws your entities.
         *
         * This is the last function that is called in a frame.
         *
         */
        void draw()
        {
            m_window->getContext().preDraw();
            impl().draw();
            m_window->getContext().postDraw();
            m_window->swap();
        }

        auto& getTimer() { return m_tickTimer; }
        auto& getWindow() { return *m_window.get(); }
        auto& getInputManager() { return m_inputManager; }
        auto& getAPIInstance() { return m_instance; }
        auto& getSwapchain() { return m_swapchain; }
        auto& getDevice() { return m_device; }

    private:
        inline Derived& impl() { return *static_cast<Derived*>(this); }

        void run()
        {
            init();
            while (!m_window->isWindowClosed())
            {
                m_tickTimer.update();

                processInputs();

                update();

                draw();
            }
        }

        TickTimer m_tickTimer;

        std::unique_ptr<Window<APINum>> m_window;

        bool m_isWindowClosed = false;

        InputManager m_inputManager;
        API::Instance<APINum> m_instance;
        API::Swapchain<APINum> m_swapchain;
        API::Device<APINum> m_device;

        // yeah. GLFW.
        friend void tewi::glfwKeyboardCallback<Derived, APINum>(GLFWwindow* window, int key, int scancode, int action, int mods);
        friend void tewi::glfwMouseCallback<Derived, APINum>(GLFWwindow* window, int button, int action, int mods);
        friend void tewi::glfwCursorPosCallback<Derived, APINum>(GLFWwindow* window, double xpos, double ypos);
    };
}

#include "Platform/NullRenderer/GameCommon.hpp"
