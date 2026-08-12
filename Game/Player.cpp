#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"
#include "Particle.h"
#include "SpaceGame.h"

void Player::Update(float dt) {

    // movement
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust =  m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * thrust;
    AddVelocity(velocity * dt);

    // fire
    m_fireTimer -= dt;
    if (m_fireTimer <=0 && nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_fireTimer = 0.5f;
        BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "PlayerBullet";
        //desc.model = Assets::bulletModel;
        desc.texture = nu::Resources().Get<nu::Texture>("Textures/bullet.png", nu::Engine::Get().GetRenderer());
        desc.transform = m_transform;
        desc.transform.scale = 1.0f;
        desc.speed = 400.0f;
        desc.lifespan = 3.0f;

        // create bullets

        m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

        desc.transform.rotation += 20.0f;
        m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

        desc.transform.rotation -= 40.0f;
        m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

        nu::Engine::Get().GetAudio().PlaySound("Fire");
        

    }

    if (thrust) {
        //ParticleDesc particleDesc;
        //particleDesc.name = "Particle";
        //particleDesc.tag = "PlayerParticle";
        ////desc.model = Assets::bulletModel;
        //switch (nu::RandomInt(4)) {
        //case 0:
        //    particleDesc.texture = nu::Resources().Get<nu::Texture>("Textures/blackParticle.png", nu::Engine::Get().GetRenderer());
        //    break;
        //case 1:
        //    particleDesc.texture = nu::Resources().Get<nu::Texture>("Textures/redParticle.png", nu::Engine::Get().GetRenderer());
        //    break;
        //case 2:
        //    particleDesc.texture = nu::Resources().Get<nu::Texture>("Textures/yellowParticle.png", nu::Engine::Get().GetRenderer());
        //    break;
        //case 3:
        //    particleDesc.texture = nu::Resources().Get<nu::Texture>("Textures/whiteParticle.png", nu::Engine::Get().GetRenderer());
        //    break;
        //default:
        //    break;
        //}
        //
        //particleDesc.transform = m_transform;
        //particleDesc.transform.scale = 0.1f;
        //particleDesc.speed = -400.0f;
        //particleDesc.lifespan = 2.0f;

        //m_scene->AddActor(std::move(std::make_unique<Particle>(particleDesc)));

        //particleDesc.transform.rotation += nu::RandomFloat(20.0f);
        //m_scene->AddActor(std::move(std::make_unique<Particle>(particleDesc)));

        //particleDesc.transform.rotation -= nu::RandomFloat(40.0f);
        //m_scene->AddActor(std::move(std::make_unique<Particle>(particleDesc)));

        nu::Particle particle;

        nu::Vector2 offset{ -20.0f, 0.0f };
        offset = offset.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f);

        nu::Color colors[3] = { { 1.0f, 1.0f, 1.0f }, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f} };
        particle.position = m_transform.position + offset;
        //particle.color = colors[nu::RandomInt(3)];
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
        //{ nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

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
    if (other->GetName() == "Enemy") {
        //nu::Engine::Get().GetAudio().PlaySound("Explosion");
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
}

void Player::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}

