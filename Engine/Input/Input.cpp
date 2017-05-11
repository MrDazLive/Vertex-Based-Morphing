#include "Input.h"

glm::vec2                   Input::m_cursorPosition;
Input::Array<KeyState>      Input::m_keyState{};
Input::ArrayBinding         Input::m_keyBinding[3]{};

const glm::vec2& Input::getCursorPosition() {
    return m_cursorPosition;
}

const bool Input::getButton(const KeyCode key, const KeyState state) {
    return m_keyState[(unsigned int)key] == state;
}

void Input::Initialise() {
    for (unsigned int i = 0; i < 255; i++) {
        m_keyState[i] = KeyState::FREE;
    }
}

void Input::OnUpdate() {
    for (unsigned int i = 0; i < 255; i++) {
        KeyState &state = m_keyState[i];
        if (state < KeyState::FREE) {
            KeyboardHandle((KeyCode)i, state);
            if (state == KeyState::UP) state = KeyState::FREE;
            if (state == KeyState::DOWN) state = KeyState::HOLD;
        }
    }
}

void Input::BindKey(const KeyCode key, const KeyState state, KeyBinding action) {
    Input::m_keyBinding[(unsigned int)state][(unsigned int)key].push_back(action);
}

void Input::KeyboardFunction(unsigned char key, int x, int y) {
    KeyState &state = m_keyState[key];
    state = state == KeyState::FREE ? KeyState::DOWN : KeyState::HOLD;
}

void Input::KeyboardReleaseFunction(unsigned char key, int x, int y) {
    m_keyState[key] = KeyState::UP;
}

void Input::KeyboardSpecialFunction(int key, int x, int y) {
    KeyboardFunction(key + 127, x, y);
}

void Input::KeyboardSpecialReleaseFunction(int key, int x, int y) {
    KeyboardReleaseFunction(key + 127, x, y);
}

void Input::CursorFunction(int x, int y) {
    m_cursorPosition = { x, y };
}

void Input::MouseFunction(int key, int state, int x, int y) {
    switch (state) {
    case 0:
        KeyboardFunction(key, x, y);
        break;
    case 1:
        KeyboardReleaseFunction(key, x, y);
        break;
    default:
        break;
    }
}

void Input::KeyboardHandle(const KeyCode key, const KeyState state) {
    for (KeyBinding binding : m_keyBinding[(unsigned int)state][(unsigned int)key]) {
        binding();
    }
}