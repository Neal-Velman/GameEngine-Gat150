#pragma once

#include "Actor.h"

struct BulletDesc : public nu::ActorDesc {
	float speed { 0.0f };
};

class Bullet : public nu::Actor {
public:
	Bullet() = default;
	Bullet(const BulletDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}

	void Update(float dt) override;

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
};