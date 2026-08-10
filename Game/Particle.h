#pragma once

#include "Actor.h"

struct ParticleDesc : public nu::ActorDesc {
	float speed{ 0.0f };
};

class Particle : public nu::Actor {
public:
	Particle() = default;
	Particle(const ParticleDesc& ParticleDesc) : Actor{ ParticleDesc }, m_speed{ ParticleDesc.speed } {}

	void Update(float dt) override;

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
};