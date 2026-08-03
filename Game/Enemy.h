#pragma once

#include "Actor.h"

struct EnemyDesc : public nu::ActorDesc {
	float speed{ 0.0f };
	float health{ 1.0f };
	int points{ 100 };
};

class Enemy : public nu::Actor {
public:
	Enemy() = default;
	Enemy(const EnemyDesc& enemyDesc) : Actor{ enemyDesc }, m_speed{ enemyDesc.speed }, m_health{ enemyDesc.health }, m_points{ enemyDesc.points } {}
	Enemy(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {}
	Enemy(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
	float m_health = 1.0f;
	int m_points = 100;
};