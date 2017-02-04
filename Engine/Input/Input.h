#pragma once

#include <array>
#include <vector>
#include <functional>

#include "../Enumerators/KeyCode.h"
#include "../Enumerators/KeyState.h"

template <typename T>	using Array			= std::array<T, 152>;
						using Binding		= std::function<void(void)>;
						using ArrayBinding	= Array<std::vector<Binding>>;

class Input final {
public:
	static void		BindKey							(const KeyCode, const KeyState, Binding);
	static void		KeyboardFunction				(unsigned char, int, int);
	static void		KeyboardReleaseFunction			(unsigned char, int, int);

	static void		KeyboardSpecialFunction			(int, int, int);
	static void		KeyboardSpecialReleaseFunction	(int, int, int);
private:
	Input() = default;

	static void		KeyboardHandle					(const KeyCode, const KeyState);

	static Array<KeyState>	m_keyState;
	static ArrayBinding		m_keyBinding[3];
};