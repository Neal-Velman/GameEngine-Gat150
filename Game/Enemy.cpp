#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

void Enemy::Update(float dt) {

    Player* player = m_scene->GetActorByName<Player>("Player");

    if (player) {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * 180.0f / 3.1415926535897932384626433832795f);
        nu::Vector2 forward { 1,0 };
        forward = forward.Rotate(m_transform.rotation * (3.1415926535897932384626433832795f / 180.0f));
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;
    float rotate = 0.0f;

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * thrust;
    AddVelocity(velocity * dt);

    Actor::Update(dt);

}

void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "PlayerBullet") {
        other->SetDestroyed();
        m_health -= 1.0f;
        if (m_health <= 0.0f) {
            nu::Engine::Get().GetAudio().PlaySound("Explosion");
            SetDestroyed();
            for (int i = 0; i < 100; i++)
            {
                nu::Particle particle;
                particle.position = m_transform.position;
                particle.color = { 1.0f, 1.0f, 1.0f };
                particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
                particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

                nu::Engine::Get().GetPS().AddParticle(particle);
            }
            ((SpaceGame*)m_scene->GetGame())->AddPoints(m_points);
        }
    }
}
