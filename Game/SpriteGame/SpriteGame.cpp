#include "SpriteGame.h"
#include "Engine.h"
#include <memory>

bool SpriteGame::Initialize() {
    nu::SetWorkingDirectory("SpriteGame");
    Game::Initialize();

    m_scene = std::make_unique<nu::Scene>();
    m_scene->SetGame(this);
    m_scene->Load("Data/scene.json");
    m_gameState = GameState::TITLE;
    m_spawnTime = 2.5f;

    nu::Engine::Get().GetAudio().AddSound("Fire", "Audio/snd_fire.wav");
    //nu::Engine::Get().GetAudio().AddSound("Explosion", "Audio/explosion.wav");
    m_titleText = new nu::Text(nu::Resources().Get<nu::Font>("Fonts/BitcountGridDouble-Black.ttf", 64.0f));
    m_scoreText = new nu::Text(nu::Resources().Get<nu::Font>("Fonts/BitcountGridDouble-Black.ttf", 32.0f));
    m_livesText = new nu::Text(nu::Resources().Get<nu::Font>("Fonts/BitcountGridDouble-Black.ttf", 32.0f));
    
    return true;
}

using namespace nu;
void SpriteGame::Update(float dt) {
    switch (m_gameState) {
    case GameState::TITLE:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::START_GAME;
        }
        break;
    case GameState::START_GAME:
        m_score = 0;
        m_lives = 3;
        m_spawnTime = 5.0f;
        m_stateTimer = 0.5f;
        m_gameState = GameState::START_LEVEL;
        break;
    case GameState::START_LEVEL:
        m_scene->RemoveAllActors();
        SpawnPlayer();
        m_scene->Load("Data/level.json");
        //m_spawnTime = 5.0f;
        m_gameState = GameState::GAME;
        break;
    case GameState::GAME:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0.0f) {
            m_spawnTimer = m_spawnTime;
            SpawnEnemy();
            // increase difficulty
            m_spawnCount++;
            if (m_spawnCount > 5 && m_spawnTime >= 1.0f) {
                m_spawnCount = 0;
                m_spawnTime -= 0.5f;
            }
        }
        break;
    case GameState::GAME_OVER:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_scene->RemoveAllActors();
            m_gameState = GameState::TITLE;
        }
        break;
    default:
        break;
    }
    Game::Update(dt);
}

void SpriteGame::Draw(nu::Renderer& renderer) {
	renderer.EnableCamera(false);
    nu::Engine::Get().GetRenderer().DrawBackground(*nu::Resources().Get<nu::Texture>("Textures/bg03.png", nu::Engine::Get().GetRenderer()), 30, 30, 0.0f, 30);
    switch (m_gameState) {
    case GameState::TITLE:
        m_titleText->Create(nu::Engine::Get().GetRenderer(), "Totally Realistic Sprite-Based Combat", nu::Color{ 1.0f, 1.0f, 1.0f });
        m_titleText->Draw(renderer, 400, 400);
        break;
    case GameState::START_GAME:
        break;
    case GameState::START_LEVEL:
        break;
    case GameState::GAME:
        m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, 30, 30);

        m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        m_livesText->Draw(renderer, (float)renderer.GetWidth() - 360, (float)30);
        break;
    case GameState::GAME_OVER:
        break;
    default:
        break;
    }
    renderer.EnableCamera();
    Game::Draw(renderer);
}

void SpriteGame::OnPlayerDead() {
    m_lives--;
    m_gameState = (m_lives == 0) ? GameState::GAME_OVER : GameState::START_LEVEL;
}

void SpriteGame::SpawnPlayer() {

    auto actor = nu::Factory::Instance().Create<nu::Actor>("PlayerPrototype");
    m_scene->AddActor(std::move(actor));
}

void SpriteGame::SpawnEnemy() {
    int enemyIndex = nu::RandomInt(2);
    if (enemyIndex == 0) {
        auto actor = nu::Factory::Instance().Create<nu::Actor>("EnemyPrototype");
        actor->SetPosition(nu::Vector2{ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
        m_scene->AddActor(std::move(actor));
    }
    else if (enemyIndex == 1) {
        auto actor = nu::Factory::Instance().Create<nu::Actor>("FlyingEnemyPrototype");
        actor->SetPosition(nu::Vector2{ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
        m_scene->AddActor(std::move(actor));
    }  
}