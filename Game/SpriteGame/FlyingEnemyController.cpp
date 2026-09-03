#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Damager.h"
#include "SpriteGame.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	CharacterBase::Start();
	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
	m_points = 150;
}

void FlyingEnemyController::Update(float dt) {

	
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state) {
	case CharacterBase::State::MOVE:
	{
		
		auto player = m_scene->GetActorByName("PlayerPrototype");

		if (player) {
			nu::Vector2 position = GetTransform().position;
			nu::Vector2 playerPosition = player->GetTransform().position;

			nu::Vector2 direction = playerPosition - position;

			if (direction.Length() < 100.0f) {
				m_state = State::ATTACK;
				m_rendererComponent->Play(nu::ToLower("attack"));

				auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
				damager->SetDamage(3.0f);
				damager->SetPosition(GetTransform().position);
				damager->SetScale(1.0f);
				damager->SetTag("EnemyDamager");
				m_scene->AddActor(std::move(damager));
				m_hasAttacked = false;
			}

			m_physicsComponent->ApplyForce(direction.Normalized() * 1000.0f);
		}
	}
	break;
	case CharacterBase::State::ATTACK:
		if (m_hasAttacked == false && m_rendererComponent->GetFrame() == 3) {
			m_hasAttacked = true;
			// Put damager code in here
		}

		if (m_rendererComponent->IsAnimationDone()) {
			m_state = State::MOVE;
			m_rendererComponent->Play(nu::ToLower("idle"));
		}
		break;
	case CharacterBase::State::HIT:
		m_physicsComponent->ApplyForce(nu::Vector2{ 0.0f, -10000.0f/*nu::RandomFloat(-250.0f, -500.0f)*/ });
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = State::MOVE;
			m_rendererComponent->Play(nu::ToLower("idle"));
		}
		break;
	case CharacterBase::State::DEATH:
		if (GetDestroyed()) {
			((SpriteGame*)m_scene->GetGame())->AddPoints(m_points);
		}
		break;
	default:
		break;
	}

	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(nu::Actor* other) {
	if (other->GetTag() == "PlayerDamager") {
		other->SetDestroyed();
		m_state = State::HIT;
		m_rendererComponent->Play(nu::ToLower("hit"));
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) {
			m_health -= damager->GetDamage();
		}
		if (m_health <= 0) {
			m_state = State::DEATH;
			SetDestroyed();
			
		}
	}
}

void FlyingEnemyController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}

