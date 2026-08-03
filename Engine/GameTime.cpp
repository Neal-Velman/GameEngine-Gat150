#include "pch.h"
#include "GameTime.h"
#include <SDL3/SDL.h>

namespace nu {

	Time::Time() {
		Reset();
	}

	void Time::Reset() {
		m_startTicks = SDL_GetTicksNS();
		m_frameTicks = SDL_GetTicksNS();
		m_currentTicks = SDL_GetTicksNS();
	}

	void Time::Tick() {
		m_currentTicks = SDL_GetTicksNS();
		m_deltaTicks = m_currentTicks - m_frameTicks; // delta = current ticks - previous ticks
		m_frameTicks = m_currentTicks; // set previous ticks
	}

}

