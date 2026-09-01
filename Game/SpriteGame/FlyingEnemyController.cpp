#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Core/Factory.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {

	Actor::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	auto player = m_scene->GetActorByName("PlayerPrototype");

	if (player) {
		nu::Vector2 position = GetTransform().position;
		nu::Vector2 playerPosition = player->GetTransform().position;

		nu::Vector2 direction = playerPosition - position;

		m_physicsComponent->ApplyForce(direction.Normalized() * 1000.0f);
	}

	Actor::Update(dt);
}

void FlyingEnemyController::OnCollision(nu::Actor* other) {

}

void FlyingEnemyController::Read(const nu::json::value_t& value) {
	Actor::Read(value);
}

