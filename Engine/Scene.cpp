#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace nu {

	void Scene::AddActor(Actor* actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(actor);
	}

	void Scene::RemoveAllActors() {
		for (auto actor : m_actors) {
			delete actor;
		}

		m_actors.clear();
	}

	void Scene::Update(float dt) {
		for (auto actor : m_actors) {
			actor->Update(dt);
		}
		UpdateCollisions();

		std::erase_if(m_actors, [](auto actor) { return actor->m_destroyed; });
		

		// ADD PENDING ACTORS
		m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());
		m_pendingActors.clear();
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