#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Core/Factory.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {

	Actor::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	float dir = 0.0f;
	auto player = m_scene->GetActorByName("PlayerPrototype");

	if (player) {
		nu::Vector2 position = GetTransform().position;
		nu::Vector2 playerPosition = player->GetTransform().position;

		if (playerPosition.x < position.x) {
			dir = -1.0f; 
		} else {
			dir = 1.0f;
		}
	}

	if (dir != 0.0f) {
		velocity.x = dir * 100.0f;
		m_rendererComponent->Play("run");
	}
	else {
		m_rendererComponent->Play("idle");
	}
	//m_rendererComponent->SetFlipH(dir < 0.0f);

	m_physicsComponent->SetVelocity(velocity);
	Actor::Update(dt);
}

void EnemyController::OnCollision(nu::Actor* other) {

}

void EnemyController::Read(const nu::json::value_t& value) {
	Actor::Read(value);
}

