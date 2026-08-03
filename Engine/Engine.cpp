// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include "Engine.h"
// TODO: This is an example of a library function

namespace nu {
	bool Engine::Initialize() {
		m_renderer.Initialize("Game Engine", 1920, 1024);
		m_input.Initialize();
		m_audio.Initialize();
		m_particleSystem.Initialize(5000);
		return true;
	}

	void Engine::Shutdown() {

		m_input.Shutdown();
		m_particleSystem.Shutdown();
		m_renderer.Shutdown();
		m_audio.Shutdown();
	}

	void Engine::Update() {

		m_time.Tick();
		m_input.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
		m_audio.Update();
	}

}
