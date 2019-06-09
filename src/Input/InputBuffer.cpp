#include <tewi/Input/InputBuffer.hpp>

namespace tewi
{

    void InputBuffer::keyCallback(GLFWwindow* win, int key, int /* scancode */,
                                  int action, int mods)
    {
        auto ptr = static_cast<InputBuffer*>(glfwGetWindowUserPointer(win));

        tewi::WindowEvent event;

        switch (key)
        {
        case GLFW_KEY_UNKNOWN:
            event.type = WindowEvent::Type::Unknown;
            break;
        default:
            event.type = static_cast<WindowEvent::Type>(key);
        }

        switch (action)
        {
        case GLFW_PRESS:
            event.action = WindowEvent::Action::Press;
            break;

        case GLFW_RELEASE:
            event.action = WindowEvent::Action::Release;
            break;

        case GLFW_REPEAT:
            event.action = WindowEvent::Action::Repeat;
            break;
        default:
            event.action = WindowEvent::Action::None;
        }

        switch (mods)
        {
        case GLFW_MOD_SHIFT:
            event.mod = WindowEvent::Modifier::Shift;
            break;
        case GLFW_MOD_ALT:
            event.mod = WindowEvent::Modifier::Alt;
            break;
        case GLFW_MOD_CONTROL:
            event.mod = WindowEvent::Modifier::Ctrl;
            break;
        case GLFW_MOD_SUPER:
            event.mod = WindowEvent::Modifier::Super;
            break;
        default:
            event.mod = WindowEvent::Modifier::None;
        }

        ptr->m_queue.push(event);
    }

    void InputBuffer::preFrame()
    {
        m_queue.reset();
    }

    gsl::span<tewi::WindowEvent> InputBuffer::queryEvents()
    {
        if (m_queue.empty())
        {
            return { gsl::null_span {} };
        }

        return gsl::span<tewi::WindowEvent> { m_queue.begin(), m_queue.end() };
    }
} // namespace tewi
