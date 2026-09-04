#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Framework/Scene.h"
#include "Damager.h"
#include "SpriteGame.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start() {

	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
	m_points = -500;
}

void PlayerController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state) {
	case CharacterBase::State::MOVE:
	{
		float dir = 0.0f;
		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -2.0f;
		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +2.0f;
		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			velocity.y = -750.0f;
		}

		if (dir != 0.0f) {
			velocity.x = dir * 100.0f;
			m_rendererComponent->Play(nu::ToLower("run"));
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else {
			m_rendererComponent->Play(nu::ToLower("idle"));
		}

		if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RSHIFT)) {
			m_state = State::ATTACK;
			m_rendererComponent->Play(nu::ToLower("attack"));

			auto damager = nu::Factory::Instance().Create<nu::Actor>("DamagerPrototype");
			damager->SetPosition(GetTransform().position + nu::Vector2{(m_rendererComponent->GetFlipH()) ? -50.0f : 50.0f, 20.0f});
			damager->SetTag("PlayerDamager");
			damager->SetScale(2.0f);
			m_scene->AddActor(std::move(damager));
		}
	}
		break;
	case CharacterBase::State::ATTACK:
	{

		if (m_rendererComponent->IsAnimationDone()) {
			m_state = State::MOVE;
			m_rendererComponent->Play(nu::ToLower("idle"));
		}
	}
		break;
	case CharacterBase::State::HIT:
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = State::MOVE;
			m_rendererComponent->Play(nu::ToLower("idle"));
		}
		break;
	case CharacterBase::State::DEATH:
		if (GetDestroyed()) {
			((SpriteGame*)m_scene->GetGame())->OnPlayerDead();
			((SpriteGame*)m_scene->GetGame())->AddPoints(m_points);
		}
		break;
	default:
		break;
	}

	m_physicsComponent->SetVelocity(velocity);
	nu::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());
	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* other) {
	if (other->GetTag() == "EnemyDamager") {
		other->SetDestroyed();
		m_state = State::HIT;
		m_rendererComponent->Play(nu::ToLower("death"));
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

void PlayerController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}

