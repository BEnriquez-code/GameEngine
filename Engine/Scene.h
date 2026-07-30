#pragma once
#include "Actor.h"
#include <string>
#include <vector>

namespace nu{
	class Scene {

	public:
		void AddActor(Actor* actor);
		std::vector<Actor*> GetActors() { return m_actors; };
		void RemoveAllActors();

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		template<typename T>
		T* GetActorByName(const std::string& name);

		void SetGame(class Game* game) { m_game = game; };
		class Game* GetGame() { return m_game; };

	private:
		void UpdateCollisions();

		std::vector<Actor*> m_actors;
		std::vector<Actor*>m_pendingActors;

		class Game* m_game{ nullptr };
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name) {
		for (auto actor : m_actors) {
			T* actorT = dynamic_cast<T*>(actor);
			if (actorT && actorT->m_name == name) {
				return actorT;
			}
		}

		return nullptr;
	}
}	