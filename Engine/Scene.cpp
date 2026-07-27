#include "pch.h"
#include "Scene.h"
#include "Actor.h"


namespace nu {
	void Scene::Update(float dt) {
		for (auto actor : m_actors) {
			actor->Update(dt);
		}
		UpdateCollisions();
	}
	void Scene::Draw(const class Renderer& renderer) {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}

	}

	void Scene::UpdateCollisions() {
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB) continue;

				float distance = (actorA->GetTransform().position - actorB->GetTransform().position).Length();
				if (distance <= actorA->GetRadius() * actorB->GetRadius()) {
					actorA->OnCollision(actorB);
					actorB->OnCollision(actorA);
				}
			}
		}
	}
}