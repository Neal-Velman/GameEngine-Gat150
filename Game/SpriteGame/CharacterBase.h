#pragma once
#include "Framework/Actor.h"
class CharacterBase : public nu::Actor {
public:
	enum class State {
		MOVE,
		ATTACK,
		HIT,
		DEATH
	};

public:
	void Read(const nu::json::value_t& value) override;

protected:
	State m_state = State::MOVE;
	float m_health{ 10.0f };
	float m_stateTime{ 0.0f };
	int m_points{ 0 };


};