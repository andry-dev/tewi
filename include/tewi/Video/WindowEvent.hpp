#pragma once

#include <asl/types>

#include <tewi/Utils/Glfw.h>

namespace tewi
{
    struct WindowEvent
    {
        enum class Type : asl::i16
        {
            Unknown = 0,

            KeyEscape = GLFW_KEY_ESCAPE,

            KeySpace = GLFW_KEY_SPACE,
            KeyBackspace = GLFW_KEY_BACKSPACE,
            KeyTab = GLFW_KEY_TAB,

            KeyF1 = GLFW_KEY_F1,
            KeyF2 = GLFW_KEY_F2,
            KeyF3 = GLFW_KEY_F3,
            KeyF4 = GLFW_KEY_F4,
            KeyF5 = GLFW_KEY_F5,
            KeyF6 = GLFW_KEY_F6,
            KeyF7 = GLFW_KEY_F7,
            KeyF8 = GLFW_KEY_F8,
            KeyF9 = GLFW_KEY_F9,
            KeyF10 = GLFW_KEY_F10,
            KeyF11 = GLFW_KEY_F11,
            KeyF12 = GLFW_KEY_F12,

            Key1 = GLFW_KEY_1,
            Key2 = GLFW_KEY_2,
            Key3 = GLFW_KEY_3,
            Key4 = GLFW_KEY_4,
            Key5 = GLFW_KEY_5,
            Key6 = GLFW_KEY_6,
            Key7 = GLFW_KEY_7,
            Key8 = GLFW_KEY_8,
            Key9 = GLFW_KEY_9,
            Key0 = GLFW_KEY_0,

            KeyQ = GLFW_KEY_Q,
            KeyW = GLFW_KEY_W,
            KeyR = GLFW_KEY_R,
            KeyT = GLFW_KEY_T,
            KeyY = GLFW_KEY_Y,
            KeyU = GLFW_KEY_U,
            KeyI = GLFW_KEY_I,
            KeyO = GLFW_KEY_O,
            KeyP = GLFW_KEY_P,
            KeyA = GLFW_KEY_P,
            KeyS = GLFW_KEY_S,
            KeyD = GLFW_KEY_D,
            KeyF = GLFW_KEY_F,
            KeyG = GLFW_KEY_G,
            KeyH = GLFW_KEY_H,
            KeyJ = GLFW_KEY_J,
            KeyK = GLFW_KEY_K,
            KeyL = GLFW_KEY_L,
            KeyZ = GLFW_KEY_Z,
            KeyX = GLFW_KEY_X,
            KeyC = GLFW_KEY_C,
            KeyV = GLFW_KEY_V,
            KeyB = GLFW_KEY_B,
            KeyN = GLFW_KEY_N,
            KeyM = GLFW_KEY_M,

            KeyLeftBracket = GLFW_KEY_LEFT_BRACKET,
            KeyRightBracket = GLFW_KEY_RIGHT_BRACKET,
            KeySemicolon = GLFW_KEY_SEMICOLON,
            KeyGrave = GLFW_KEY_GRAVE_ACCENT,
            KeyApostrophe = GLFW_KEY_APOSTROPHE,
            KeyComma = GLFW_KEY_COMMA,
            KeyPeriod = GLFW_KEY_PERIOD,
            KeySlash = GLFW_KEY_SLASH,
            KeyBackslash = GLFW_KEY_BACKSLASH,
            KeyMinus = GLFW_KEY_MINUS,
            KeyEqual = GLFW_KEY_EQUAL,

            KeyLeftShift = GLFW_KEY_LEFT_SHIFT,
            KeyLeftCtrl = GLFW_KEY_LEFT_CONTROL,
            KeyLeftAlt = GLFW_KEY_LEFT_ALT,
            KeyLeftSuper = GLFW_KEY_LEFT_SUPER,
            KeyRightShift = GLFW_KEY_RIGHT_SHIFT,
            KeyRightCtrl = GLFW_KEY_RIGHT_CONTROL,
            KeyRightAlt = GLFW_KEY_RIGHT_ALT,
            KeyRightSuper = GLFW_KEY_RIGHT_SUPER,
            KeyMenu = GLFW_KEY_MENU,

            KeyUp = GLFW_KEY_UP,
            KeyLeft = GLFW_KEY_LEFT,
            KeyDown = GLFW_KEY_DOWN,
            KeyRight = GLFW_KEY_RIGHT,

            KeyInsert = GLFW_KEY_INSERT,
            KeyDelete = GLFW_KEY_DELETE,
            KeyHome = GLFW_KEY_HOME,
            KeyEnd = GLFW_KEY_END,
            KeyPageUp = GLFW_KEY_PAGE_UP,
            KeyPageDown = GLFW_KEY_PAGE_DOWN,

            KeyPrint = GLFW_KEY_PRINT_SCREEN,
            KeyScrollLock = GLFW_KEY_SCROLL_LOCK,
            KeyPause = GLFW_KEY_PAUSE,

            Mouse1 = GLFW_KEY_LAST + 1,
            Mouse2 = GLFW_KEY_LAST + 2,
            Mouse3 = GLFW_KEY_LAST + 3,
            Mouse4 = GLFW_KEY_LAST + 4,
            Mouse5 = GLFW_KEY_LAST + 5,
            Mouse6 = GLFW_KEY_LAST + 6,
            Mouse7 = GLFW_KEY_LAST + 7,
            Mouse8 = GLFW_KEY_LAST + 8,
        };

        enum class Action : asl::i8
        {
            None,
            Press,
            Release,
            Repeat,
        };

        enum class Modifier : asl::i8
        {
            None,
            Shift,
            Ctrl,
            Alt,
            Super,
        };

        WindowEvent()
            : type(Type::Unknown)
            , action(Action::None)
            , mod(Modifier::None)
        {
        }

        Type type;
        Action action;
        Modifier mod;
    };
} // namespace tewi
