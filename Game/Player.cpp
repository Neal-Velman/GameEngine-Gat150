#include "Player.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"
#include "Particle.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"

    FACTORY_REGISTER(Player)

void Player::Update(float dt) {
    // movement
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust =  m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -360.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +360.0f;



    auto physicsComponent = GetComponent<nu::PhysicsComponent>();
    if (physicsComponent) {
        nu::Vector2 forward{ 1, 0 };
        nu::Vector2 force = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * thrust;
        physicsComponent->ApplyForce(force);
        physicsComponent->ApplyTorque(rotate);

        nu::Vector2 position = physicsComponent->GetPosition();

        position.x = nu::math::Wrap(0.0f, 1920.0f, position.x);
        position.y = nu::math::Wrap(0.0f, 1024.0f, position.y);

        physicsComponent->SetPosition(position);
    }

    // fire
    m_fireTimer -= dt;
    if (m_fireTimer <=0 && nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_fireTimer = 0.5f;

        auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet->SetTransform(m_transform);
        bullet->SetTag("PlayerBullet");
        m_scene->AddActor(std::move(bullet));

        auto bullet2 = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet2->SetTransform(m_transform);
        bullet2->SetTag("PlayerBullet");
        bullet2->SetRotation(m_transform.rotation + 20.0f);
        m_scene->AddActor(std::move(bullet2));

        auto bullet3 = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet3->SetTransform(m_transform);
        bullet3->SetTag("PlayerBullet");
        bullet3->SetRotation(m_transform.rotation - 20.0f);
        m_scene->AddActor(std::move(bullet3));


        nu::Engine::Get().GetAudio().PlaySound("Fire");
    }

    if (thrust) {
        nu::Particle particle;

        nu::Vector2 offset{ -20.0f, 0.0f };
        offset = offset.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f);

        nu::Color colors[3] = { { 1.0f, 1.0f, 1.0f }, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f} };
        particle.position = m_transform.position + offset;
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
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
        particle.velocity = nu::Vector2{nu::RandomFloat(-30.0f, -100.0f), 0.0f}.Rotate((m_transform.rotation + nu::RandomInt(-25, 25)) * 3.1415926535897932384626433832795f / 180.0f);

        nu::Engine::Get().GetPS().AddParticle(particle);
    }
    

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
    return; // IMMORTALITY
    if (other->GetTag() == "Enemy") {
        //nu::Engine::Get().GetAudio().PlaySound("Explosion");
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
}

void Player::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}