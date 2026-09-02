#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Core/Factory.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start() {

	Actor::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	float dir = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1.0f;
	if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		velocity.y = -250.0f;
	}

	if (dir != 0.0f) {
		velocity.x = dir * 100.0f;
		m_rendererComponent->Play("run");
	} else {
		m_rendererComponent->Play("idle");
	}
	m_rendererComponent->SetFlipH(dir < 0.0f);

	m_physicsComponent->SetVelocity(velocity);
	nu::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());
	Actor::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* other) {

}

void PlayerController::Read(const nu::json::value_t& value) {
	Actor::Read(value);
}

