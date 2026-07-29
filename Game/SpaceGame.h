#pragma once
#include "Game.h"
#include "Vector2.h"

#include <vector>

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

	void Update(float dt, const std::vector<nu::Vector2>& mousePoints);
	void Update(float dt) override;
	void Draw(const class nu::Renderer& renderer) override;

	float PointToLineSegDistance(const nu::Vector2& A, const nu::Vector2& B, const nu::Vector2& C);
	void CheckLineCollisions(const std::vector<nu::Vector2>& mousePoints);

private:
	
	int m_score{ 0 };
	int m_lives{0};

	GameState m_gameState = GameState::Title;
};