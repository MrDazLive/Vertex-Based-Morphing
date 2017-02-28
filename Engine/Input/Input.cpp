#include "Input.h"

#include <iostream>

Input::Array<KeyState>      Input::m_keyState{};
Input::ArrayBinding         Input::m_keyBinding[3]{};

void Input::Initialise() {
    for (unsigned int i = 0; i < 255; i++) {
        m_keyState[i] = KeyState::Free;
    }
}

void Input::OnUpdate() {
    for (unsigned int i = 0; i < 255; i++) {
        KeyState &state = m_keyState[i];
        if (state != KeyState::Free) {
            KeyboardHandle((KeyCode)i, state);
            if (state == KeyState::Up) state = KeyState::Free;
        }
    }
}

void Input::BindKey(const KeyCode key, const KeyState state, KeyBinding action) {
    Input::m_keyBinding[state][key].push_back(action);
}

void Input::KeyboardFunction(unsigned char key, int x, int y) {
    KeyState &state = m_keyState[key];
    state = state == KeyState::Free ? KeyState::Down : KeyState::Hold;
}

void Input::KeyboardReleaseFunction(unsigned char key, int x, int y) {
    m_keyState[key] = KeyState::Up;
}

void Input::KeyboardSpecialFunction(int key, int x, int y) {
    KeyboardFunction(key + 127, x, y);
}

void Input::KeyboardSpecialReleaseFunction(int key, int x, int y) {
    KeyboardReleaseFunction(key + 127, x, y);
}

void Input::KeyboardHandle(const KeyCode key, const KeyState state) {
    for (KeyBinding binding : m_keyBinding[state][key]) {
        binding();
    }
}