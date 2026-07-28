#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Assets.h"

using namespace nu;

bool SpaceGame::Initialize() {
	Game::Initialize();
	m_scene = new Scene();

	return true;
}

void SpaceGame::Update(float dt) {
	switch (m_gameState){
		case GameState::Title:
			if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
				m_gameState = GameState::StartGame;
			}
			break;
		case GameState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_gameState = GameState::StartLevel;
			break;
		case GameState::StartLevel:
		{
			PlayerDesc playerDesc;
			playerDesc.name = "Player";
			playerDesc.model = assets::playerModel;
			playerDesc.transform = Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 15.0f };
			playerDesc.velocity = Vector2{ 0.0f, 0.0f };
			playerDesc.damping = 2.0f;
			playerDesc.speed = 250.0f;


			Player* player = new Player(playerDesc);
			m_scene->AddActor(player);
		}

			break;
		case GameState::Game:
			break;
		case GameState::GameOver:
			break;

	default:
		break;
	}
}

void SpaceGame::Draw(const class Renderer& renderer) {
	m_scene->Draw(renderer);
}