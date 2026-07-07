#include "pch.h"
#include "Input.h"
#include <SDL3/SDL.h>

namespace nu {
	bool Input::Initialize() {

		int numkeys;
		const bool* keyState = SDL_GetKeyboardState(&numkeys);

		m_keyStates.resize(numkeys);

		copy(keyState, keyState + numkeys, m_keyStates.begin());
		m_prevKeyStates = m_keyStates;


		return true;
	}

	void Input::Shutdown() {
		
	}

	void Input::Update() {
		m_prevKeyStates = m_keyStates;
		const bool* keyState = SDL_GetKeyboardState(NULL);
		copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());

		m_prevButtonStates = m_buttonStates;
		m_buttonStates = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
	}

}