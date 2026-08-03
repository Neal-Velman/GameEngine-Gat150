#pragma once
#include "Random.h"
#include "Vector2.h"
#include "MathUtils.h"
#include "Transform.h"
#include "Text.h"

// Systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Actor.h"
#include "Scene.h"
#include "File.h"
#include "Game.h"
#include "ParticleSystem.h"
#include "Audio.h"

#include <iostream>
#include <vector>

namespace nu {

	class Engine {

	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();
		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particleSystem; }
		Audio& GetAudio() { return m_audio; }

		//Engine

	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		ParticleSystem m_particleSystem;
		Audio m_audio;

	};
}