#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include <memory>

bool SpaceGame::Initialize() {
    Game::Initialize();

    m_scene = new nu::Scene();
    m_scene->SetGame(this);
    m_scene->Load("Data/scene.json");
    m_gameState = GameState::TITLE;
    m_spawnTime = 2.5f;

    nu::Engine::Get().GetAudio().AddSound("Fire", "Audio/snd_fire.wav");
    m_titleText = new nu::Text(nu::Resources().Get<nu::Font>("Fonts/BitcountGridDouble-Black.ttf", 64.0f));
    m_scoreText = new nu::Text(nu::Resources().Get<nu::Font>("Fonts/BitcountGridDouble-Black.ttf", 32.0f));
    m_livesText = new nu::Text(nu::Resources().Get<nu::Font>("Fonts/BitcountGridDouble-Black.ttf", 32.0f));
    
    return true;
}

using namespace nu;
void SpaceGame::Update(float dt) {
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
        m_spawnTime = 5.0f;
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

void SpaceGame::Draw(nu::Renderer& renderer) {
    nu::Engine::Get().GetRenderer().DrawBackground(*nu::Resources().Get<nu::Texture>("Textures/Background.jpg", nu::Engine::Get().GetRenderer()), 30, 30, 0.0f, 30);
    switch (m_gameState) {
    case GameState::TITLE:
        m_titleText->Create(nu::Engine::Get().GetRenderer(), "Totally Realistic Space Combat", nu::Color{ 1.0f, 1.0f, 1.0f });
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

    Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead() {
    m_lives--;
    m_gameState = (m_lives == 0) ? GameState::GAME_OVER : GameState::START_LEVEL;
}

void SpaceGame::SpawnPlayer() {

    auto actor = nu::Factory::Instance().Create<nu::Actor>("PlayerPrototype");
    m_scene->AddActor(std::move(actor));

    //nu::json::document_t document;
    //if (nu::json::Load("Data/scene.json", document)) {
    //    std::string type;
    //    JSON_READ(document, type);

    //    auto actor = nu::Factory::Instance().Create<nu::Actor>(type);
    //    actor->Read(document);

    //    std::cout << actor->GetName() << std::endl;
    //    std::cout << actor->GetTag() << std::endl;

    //    std::cout << actor->GetTransform().rotation << std::endl;

    //}
 //   PlayerDesc playerDesc;
 //   playerDesc.name = "Player";
 //   //playerDesc.model = Assets::playerModel;
	//playerDesc.texture = nu::Resources().Get<nu::Texture>("Textures/player.png", nu::Engine::Get().GetRenderer());
 //   playerDesc.transform = nu::Transform{ nu::Vector2 { 860.0f, 512.0f }, 0.0f, 1.0f };
 //   playerDesc.speed = 600.0f;
 //   playerDesc.damping = 1.5f;
 //   std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
 //   m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy() {
    int enemyIndex = nu::RandomInt(2);
    if (enemyIndex == 0) {
        auto actor = nu::Factory::Instance().Create<nu::Actor>("EnemyPrototype");
        actor->SetPosition(nu::Vector2{ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
        m_scene->AddActor(std::move(actor));
       /* EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.tag = "Enemy";
        enemyDesc.texture = nu::Resources().Get<nu::Texture>("Textures/enemy.png", nu::Engine::Get().GetRenderer());
        enemyDesc.transform = nu::Transform{ nu::Vector2 { nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 180.0f, 1.0f };
        enemyDesc.speed = nu::RandomFloat(100.0f, 300.0f);
        enemyDesc.damping = 1.5f;
        enemyDesc.health = 1.0f;
        enemyDesc.points = 100;

        m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));*/
    }
    else if (enemyIndex == 1) {
        auto actor = nu::Factory::Instance().Create<nu::Actor>("Enemy2Prototype");
        actor->SetPosition(nu::Vector2{ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
        m_scene->AddActor(std::move(actor));

        /*EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.tag = "Enemy";
        enemyDesc.texture = nu::Resources().Get<nu::Texture>("Textures/enemy2.png", nu::Engine::Get().GetRenderer());
        enemyDesc.transform = nu::Transform{ nu::Vector2 { nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 180.0f, 1.0f };
        enemyDesc.speed = nu::RandomFloat(300.0f, 600.0f);
        enemyDesc.damping = 1.5f;
        enemyDesc.health = 3.0f;
        enemyDesc.points = 500;

        m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));*/
    }
        
}