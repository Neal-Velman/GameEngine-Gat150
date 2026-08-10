#include "Particle.h"
#include "MathUtils.h"



void Particle::Update(float dt) {
	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * (3.1415926535897932384626433832795f / 180.0f)) * m_speed;
	SetVelocity(velocity);
	Actor::Update(dt);
}
