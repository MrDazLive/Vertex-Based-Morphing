#pragma once

#include <array>
#include <vector>
#include <functional>
#include <glm\vec2.hpp>

#include "../Enumerators/KeyCode.h"
#include "../Enumerators/KeyState.h"

using KeyBinding = std::function<void(void)>;

class Input final {
public:
    static const glm::vec2&     getCursorPosition               ();
    static const bool           getButton                       (const KeyCode, const KeyState);

    static void                 Initialise                      ();
    static void                 OnUpdate                        ();

    static void                 BindKey                         (const KeyCode, const KeyState, KeyBinding);
    static void                 KeyboardFunction                (unsigned char, int, int);
    static void                 KeyboardReleaseFunction         (unsigned char, int, int);

    static void                 KeyboardSpecialFunction         (int, int, int);
    static void                 KeyboardSpecialReleaseFunction  (int, int, int);

    static void                 CursorFunction                  (int, int);
    static void                 MouseFunction                   (int, int, int, int);
private:
    template <typename T>       using Array                     = std::array<T, 255>;
                                using ArrayBinding              = Array<std::vector<KeyBinding>>;

                                Input                           () = default;

    static void                 KeyboardHandle                  (const KeyCode, const KeyState);

    static glm::vec2            m_cursorPosition;
    static Array<KeyState>      m_keyState;
    static ArrayBinding         m_keyBinding[3];
};