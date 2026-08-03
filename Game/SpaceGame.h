#pragma once
#include "Game.h"
#include "Text.h"

class SpaceGame : public nu::Game {
public:
	enum class GameState {
		TITLE,
		START_GAME,
		START_LEVEL,
		GAME,
		GAME_OVER
	};
public:

	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) : Game { scene } {}

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	void OnPlayerDead();

	void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnEnemy();
private:
	int m_score { 0 };
	int m_lives { 0 };

	float m_stateTimer = 0.0f;

	float m_spawnTimer = 0.0f;
	float m_spawnTime = 5.0f;
	int m_spawnCount = 0;

	GameState m_gameState = GameState::TITLE;

	nu::Font* m_titleFont { nullptr };
	nu::Text* m_titleText { nullptr };

	nu::Font* m_gameOverFont { nullptr };
	nu::Text* m_gameOverText { nullptr };

	nu::Font* m_gameFont { nullptr };

	nu::Text* m_scoreText { nullptr };
	nu::Text* m_livesText { nullptr };

	//nu::Audio* m_shootSound { nullptr; }
};