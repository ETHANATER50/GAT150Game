#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

namespace ew {

	void ew::Scene::create(void* data) {
		engine = static_cast<Engine*>(data);
	}

	void ew::Scene::destroy() {
		removeAllGameObjects();
	}

	void ew::Scene::read(const rapidjson::Value& value) {

		const rapidjson::Value& objectsValue = value["GameObjects"];
		if (objectsValue.IsArray()) {
			readGameObjects(objectsValue);
		}

	}
	void Scene::readGameObjects(const rapidjson::Value& value) {
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject()) {
				std::string typeName;
				json::get(objectValue, "type", typeName);
				ew::GameObject* gameObject = ObjectFactory::instance().Create<GameObject>(typeName);

				if (gameObject) {
					gameObject->create(engine);
					gameObject->read(objectValue);
					addGameObject(gameObject);
				}
			}
		}
	}


	void ew::Scene::update() {
		for (auto gameObject : gameObjects) {
			gameObject->update();
		}
	}

	void ew::Scene::draw() {
		for (auto gameObject : gameObjects) {
			gameObject->draw();
		}
	}

	GameObject* ew::Scene::find(const std::string& name) {
		for (auto gameObject : gameObjects) {
			if (gameObject->name == name) {
				return gameObject;
			}
		}
		return nullptr;
	}

	void ew::Scene::addGameObject(GameObject* gameObject) {
		gameObjects.push_back(gameObject);
	}

	void ew::Scene::removeGameObject(GameObject* gameObject) {
		auto iter = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
		if (iter != gameObjects.end()) {
			(*iter)->destroy();
			delete(*iter);
			gameObjects.erase(iter);
		}
	}

	void ew::Scene::removeAllGameObjects() {
		for (auto gameObject : gameObjects) {
			gameObject->destroy();
			delete gameObject;
		}
		gameObjects.clear();
	}
}

