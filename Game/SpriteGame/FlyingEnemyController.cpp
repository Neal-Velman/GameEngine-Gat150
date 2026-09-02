#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Damager.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {

	CharacterBase::Start();

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

		if (direction.Length() < 20.0f) {
			m_state = State::ATTACK;
			m_rendererComponent->Play("AttacK");
		}

		m_physicsComponent->ApplyForce(direction.Normalized() * 1000.0f);
	}

	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(nu::Actor* other) {
	if (other->GetTag() == "PlayerDamager") {
		m_state = State::HIT;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) {
			m_health -= damager->GetDamage();
		}
		if (m_health <= 0) {
			SetDestroyed();
		}
	}
}

void FlyingEnemyController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}

