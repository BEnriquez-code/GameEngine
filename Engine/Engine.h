#pragma once
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtils.h"
#include "Transform.h"
#include <fmod.hpp>



// systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Audio.h"
#include "Actor.h"

namespace nu {
	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();
		void Update();

		Input& GetInput() { return m_input; };
		Renderer& GetRenderer() { return m_renderer; };
		Audio& GetAudio() { return m_audio; };
		Time& GetTime() { return m_time; };

	private:
		Input m_input;
		Renderer m_renderer;
		Audio m_audio;

		Time m_time;
	};
	extern Engine engine;
}