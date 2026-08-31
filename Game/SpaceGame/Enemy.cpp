#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "Particle.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"

    FACTORY_REGISTER(Enemy)
void Enemy::Update(float dt) {
    Player* player = m_scene->GetActorByName<Player>("PlayerPrototype");

    if (player) {
        auto physicsComponent = GetComponent<nu::PhysicsComponent>();
        if (physicsComponent) {
            nu::Vector2 forward{ 1, 0 };
            nu::Vector2 force = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * m_speed;

            physicsComponent->ApplyForce(force);

            nu::Vector2 direction = player->GetTransform().position - m_transform.position;
            float rotation = direction.Angle();
            physicsComponent->SetRotation(rotation /** nu::math::RadToDeg*/);

            nu::Vector2 position = physicsComponent->GetPosition();

            position.x = nu::math::Wrap(0.0f, 1920.0f, position.x);
            position.y = nu::math::Wrap(0.0f, 1024.0f, position.y);

            physicsComponent->SetPosition(position);
        }
    }

    float thrust = 0.0f;
    float rotate = 0.0f;

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * thrust;
    //AddVelocity(velocity * dt);

    Actor::Update(dt);

}

void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "PlayerBullet") {
        other->SetDestroyed();
        m_health -= 1.0f;
        if (m_health <= 0.0f) {
            //nu::Engine::Get().GetAudio().PlaySound("Explosion");
            SetDestroyed();
            for (int i = 0; i < 100; i++) {
                nu::Particle particle;
                particle.position = m_transform.position;
                switch (nu::RandomInt(4)) {
                case 0:
                    particle.texture = nu::Resources().Get<nu::Texture>("Textures/blackParticle.png", nu::Engine::Get().GetRenderer());
                    break;
                case 1:
                    particle.texture = nu::Resources().Get<nu::Texture>("Textures/redParticle.png", nu::Engine::Get().GetRenderer());
                    break;
                case 2:
                    particle.texture = nu::Resources().Get<nu::Texture>("Textures/yellowParticle.png", nu::Engine::Get().GetRenderer());
                    break;
                case 3:
                    particle.texture = nu::Resources().Get<nu::Texture>("Textures/whiteParticle.png", nu::Engine::Get().GetRenderer());
                    break;
                default:
                    break;
                }
                particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
                particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

                nu::Engine::Get().GetPS().AddParticle(particle);
            }
            ((SpaceGame*)m_scene->GetGame())->AddPoints(m_points);
        }
    }
}

void Enemy::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
    JSON_READ_NAME(value, "points", m_points);
    JSON_READ_NAME(value, "health", m_health);
}