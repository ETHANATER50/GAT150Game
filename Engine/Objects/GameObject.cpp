#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"

namespace ew {
	void GameObject::create(void* data) {
		engine = static_cast<Engine*>(data);
	}

	void GameObject::destroy() {
		removeAllComponents();
	}

	void GameObject::read(const rapidjson::Value& value) {
		json::get(value, "name", name);
		json::get(value, "position", transform.position);
		json::get(value, "scale", transform.scale);
		json::get(value, "angle", transform.angle);
	}

	void GameObject::update() {
		for (auto c : components) {
			c->update();
		}
	}

	void GameObject::draw() {
		RenderComponent* rc = getComponent<RenderComponent>();
		if (rc) {
			rc->draw();
		}
	}

	void GameObject::addComponent(Component* c) {
		components.push_back(c);

	}

	void GameObject::removeComponent(Component* c) {
		auto iter = std::find(components.begin(), components.end(), c);
		if (iter != components.end()) {
			(*iter)->destroy();
			delete (*iter);
		}
	}

	void GameObject::removeAllComponents(){
		for (auto c : components) {
			c->destroy();
			delete c;
		}
	}

}
