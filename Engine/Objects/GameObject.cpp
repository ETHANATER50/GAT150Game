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
		c->owner = this;
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
