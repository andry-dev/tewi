/// GLFW's window object.
///
/// \see [GLFW's docs](https://www.glfw.org/docs/latest/group__window.html#ga3c96d80d363e67d13a41b5d1821f3242) - External GLFW's reference.
struct GLFWwindow { };

namespace tewi
{
    /// InputManager concept.
    ///
    /// Any class implementing this concept can be used in the
    /// [Window](<> "tewi::Window::bindTo()") to retrieve inputs and present them
    /// to the user.
    ///
    /// \notes This concept doesn't provide any function to provide inputs to
    ///        the user. Any implementation will have its method to provide
    ///        any input.
    ///
    /// \module Concepts
    ///
    /// \see [InputBuffer](<> "tewi::InputBuffer") - An example implementation of an `InputManager`.
    struct InputManager
    {
        /// \exclude
        using interface_only = void;

        /// GLFW's key callback.
        ///
        /// \see [GLFW's docs](https://www.glfw.org/docs/latest/group__input.html#ga0192a232a41e4e82948217c8ba94fdfd)
        static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);

        /// Action to be performed before a frame starts.
        /// It can be empty.
        void preFrame();
    };
}
