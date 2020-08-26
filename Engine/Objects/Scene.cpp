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
		if (value.HasMember("Prototypes")) {
			const rapidjson::Value& objectsValue = value["Prototypes"];
			if (objectsValue.IsArray()) {
				readPrototypes(objectsValue);
			}
		}
		if (value.HasMember("GameObjects")) {
			const rapidjson::Value& objectsValue = value["GameObjects"];
			if (objectsValue.IsArray()) {
				readGameObjects(objectsValue);
			}
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

	void Scene::readPrototypes(const rapidjson::Value& value) {
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject()) {
				std::string typeName;
				json::get(objectValue, "type", typeName);
				ew::GameObject* gameObject = ObjectFactory::instance().Create<GameObject>(typeName);

				if (gameObject) {
					gameObject->create(engine);
					gameObject->read(objectValue);

					ObjectFactory::instance().Register(gameObject->name, new Prototype<Object>(gameObject));
				}
			}
		}
	}

	void ew::Scene::update() {
		for (auto gameObject : gameObjects) {
			gameObject->update();
		}

		auto iter = gameObjects.begin();
		while (iter != gameObjects.end()) {
			if ((*iter)->flags[GameObject::eFlags::DESTROY]) {
				(*iter)->destroy();
				delete (*iter);
				iter = gameObjects.erase(iter);
			}
			else {
				iter++;
			}
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

	std::vector<GameObject*> Scene::findGameObjectsWithTag(const std::string& tag) {
		std::vector<GameObject*> gameObjects;

		for (auto gameObject : gameObjects) {
			if (gameObject->tag == tag) {
				gameObjects.push_back(gameObject);
			}
		}

		return gameObjects;
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

