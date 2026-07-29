#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <algorithm>
#include <vector>

using namespace nu;

bool SpaceGame::Initialize() {
	Game::Initialize();
	m_scene = new Scene();

	return true;
}


void SpaceGame::Update(float dt, const std::vector<nu::Vector2>& mousePoints) {
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
			CheckLineCollisions(mousePoints);
			break;
		case GameState::GameOver:
			break;

	default:
		break;
	}

	m_scene->Update(dt);
}

void SpaceGame::Update(float dt)
{
}

void SpaceGame::Draw(const class Renderer& renderer) {
	m_scene->Draw(renderer);
}

float SpaceGame::PointToLineSegDistance(const nu::Vector2& A, const nu::Vector2& B, const nu::Vector2& C) {
	Vector2 AB = B - A;
	Vector2 AC = C - A;

	float lengthSq = AB.x * AB.x + AB.y * AB.y;
	if (lengthSq == 0.0f) return (C - A).Length();

	float t = (AC.x * AB.x + AC.y * AB.y) / lengthSq;
	t = std::clamp(t, 0.0f, 1.0f);

	Vector2 projection = A + AB * t;
	return (C - projection).Length();
}

void SpaceGame::CheckLineCollisions(const std::vector<Vector2>& mousePoints) {
	if (mousePoints.size() < 2) return;

	// Iterate through line segments
	for (size_t i = 0; i < mousePoints.size() - 1; ++i) {
		Vector2 p1 = mousePoints[i];
		Vector2 p2 = mousePoints[i + 1];

		auto actors = m_scene->GetActors();
		for (auto actor : actors) {
			// Check collision for both Enemies and Bullets
			if (actor->GetTag() == "Enemy" || actor->GetTag() == "Bullet" || actor->GetTag() == "EnemyBullet") {
				Vector2 pos = actor->GetTransform().position;
				float radius = actor->GetRadius(); // Adjust based on actor's radius/size getter

				if (PointToLineSegDistance(p1, p2, pos) <= radius) {
					// Collision action:
					if (actor->GetTag() == "Enemy") {
						Vector2 pushDir = (pos - (p1 + p2) * 0.5f).Normalized();
						actor->SetVelocity(pushDir * 300.0f);
					}
					else if (actor->GetTag() == "Bullet" || actor->GetTag() == "EnemyBullet") {
						// Block and destroy incoming bullets
						actor->SetDestroyed();
					}
				}
			}
		}
	}
}

void SpaceGame::Shutdown() {
	delete m_scene;
	m_scene = nullptr;
}