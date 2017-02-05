#include "Input.h"

#include <iostream>

Input::Array<KeyState>		Input::m_keyState;
Input::ArrayBinding			Input::m_keyBinding[3]{};

void Input::BindKey(const KeyCode key, const KeyState state, KeyBinding action) {
	Input::m_keyBinding[state][key].push_back(action);
}

void Input::KeyboardFunction(unsigned char key, int x, int y) {
	KeyState &state = m_keyState[key];
	KeyboardHandle((KeyCode)key, state);
	state = KeyState::Hold;
}

void Input::KeyboardReleaseFunction(unsigned char key, int x, int y) {
	m_keyState[key] = KeyState::Down;
	KeyboardHandle((KeyCode)key, KeyState::Up);
}

void Input::KeyboardSpecialFunction(int key, int x, int y) {
	key += 127;
	KeyState &state = m_keyState[key];
	KeyboardHandle((KeyCode)key, state);
	state = KeyState::Hold;
}

void Input::KeyboardSpecialReleaseFunction(int key, int x, int y) {
	key += 127;
	m_keyState[key] = KeyState::Down;
	KeyboardHandle((KeyCode)key, KeyState::Up);
}

void Input::KeyboardHandle(const KeyCode key, const KeyState state) {
	for (KeyBinding binding : m_keyBinding[state][key]) {
		binding();
	}
}