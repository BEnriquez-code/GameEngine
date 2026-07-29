#pragma once
#include "Game.h"

class SpaceGame : public nu::Game {

public:
	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) :
		Game{ scene } {}

	bool Initialize() override;
	void Shutdown() override;

	void Update(float dt) override;
	void Draw(const class nu::Renderer& renderer) override;

private:
	int m_score{ 0 };
	int m_lives{0};

	GameState m_gameState = GameState::Title;
};