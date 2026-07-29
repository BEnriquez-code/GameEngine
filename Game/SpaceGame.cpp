#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <iostream>

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

		{
			for (int i = 0; i < 20; i++) {
				EnemyDesc enemyDesc;
				enemyDesc.name = "Enemy";
				enemyDesc.tag = "Enemy";
				enemyDesc.model = assets::enemyModel;
				enemyDesc.transform = Transform{ Vector2{RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
				enemyDesc.damping = 3.0f;
				enemyDesc.speed = RandomFloat(1000.0f, 1500.0f);

				Enemy* enemy = new Enemy(enemyDesc);
				m_scene->AddActor(enemy);
				
			}
		}

			m_gameState = GameState::Game;
			break;
		case GameState::Game:
			break;
		case GameState::GameOver:
			break;

	default:
		break;
	}

	m_scene->Update(dt);
}

void SpaceGame::Draw(const class Renderer& renderer) {
	m_scene->Draw(renderer);
}

void SpaceGame::Shutdown() {
	delete m_scene;
	m_scene = nullptr;
}