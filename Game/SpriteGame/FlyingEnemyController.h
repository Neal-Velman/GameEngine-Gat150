#pragma once
#include "Framework\Actor.h"

namespace nu {
	class PhysicsComponent;
	class SpriteAnimatorRendererComponent;
}

class FlyingEnemyController : public nu::Actor {
public:
	CLASS_PROTOTYPE(FlyingEnemyController)

	void Start() override;
	void Update(float dt) override;
	void OnCollision(nu::Actor* other) override;

	void Read(const nu::json::value_t& value) override;

protected:
	nu::PhysicsComponent* m_physicsComponent{ nullptr };
	nu::SpriteAnimatorRendererComponent* m_rendererComponent{ nullptr };
};

