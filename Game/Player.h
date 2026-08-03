#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc {
	float speed;
};

class Player : public nu::Actor{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }, m_speed{ playerDesc.speed } {}
	Player(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed { speed } {}
	Player(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update	(float dt) override;

	void OnCollision(Actor* other);

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
	float m_fireTimer = 0.0f;
};