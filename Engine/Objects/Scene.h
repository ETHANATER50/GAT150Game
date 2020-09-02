#pragma once
#include "Object.h"

namespace ew {
	class Engine;
	class GameObject;

	class Scene : public Object {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;

		void read(const rapidjson::Value& value) override;
		void readGameObjects(const rapidjson::Value& value);
		void readPrototypes(const rapidjson::Value& value);


		void update() override;
		void draw();

		GameObject* find(const std::string& name);
		std::vector<GameObject*> findGameObjectsWithTag(const std::string& tag);

		void addGameObject(GameObject* gameObject);
		void removeGameObject(GameObject* gameObject);
		void removeAllGameObjects();

		Engine* engine{ nullptr };

	protected:
		std::list<GameObject*> gameObjects;
	};
}