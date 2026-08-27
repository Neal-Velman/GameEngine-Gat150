#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Components/ColliderComponent.h"

namespace nu {

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor)); 
	}

	void Scene::RemoveAllActors(bool force) {
		// delete actors
		std::erase_if(m_actors, [force](auto& actor) { return !actor->GetPersistent() || force; });
	}

	bool Scene::Load(const std::string& sceneName) {
		json::document_t document;
		if (json::Load(sceneName, document)) {
			if (JSON_HAS_NAME(document, "actors")) {
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray()) {
					//Get actor type
					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					//Create actor of type
					auto actor = Factory::Instance().Create<Actor>(typeName);

					//Read actor JSON
					actor->Read(actorValue);

					// check if prototype
					bool prototype = false;
					JSON_READ(actorValue, prototype);


					if (prototype) {
						// if prototype, add prototype to factory registry
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					} else {
						// Not prototype, add actor to scene
						AddActor(std::move(actor));
					}
				}
			}
		} else {
			return false;
		}
		return true;
	}

	void Scene::Update(float dt) {
		// uodate actors
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}
		// update collisions
		//UpdateCollisions();

		//remove destroyed actors
		for (auto& actor : m_actors) {
			if (actor->m_destroyed) {
				actor->OnDestroy();
			}
		}
		std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });

		// add pending actors
		for (auto& actor : m_pendingActors) {
			actor->Start();
			m_actors.push_back(std::move(actor));
		}
		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (const auto& actor : m_actors) {
			if (actor) {
				actor->Draw(renderer);
			}
		}
	}

	void Scene::UpdateCollisions() {
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				// Check for self, or destroyed objects
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) { continue; }

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) { continue; }

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}