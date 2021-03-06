#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "ObjectFactory.h"
#include "Scene.h"

namespace ew {
	GameObject::GameObject(const GameObject& other) {
		name = other.name;
		tag = other.tag;
		flags = other.flags;
		lifetime = other.lifetime;
		transform = other.transform;
		engine = other.engine;
		scene = other.scene;

		for (auto component : other.components) {
			Component* clone = static_cast<Component*>(component->clone());
			clone->owner = this;
			addComponent(clone);
		}

	}

	void GameObject::create(void* data) {
		scene = static_cast<Scene*>(data);
		engine = scene->engine;
	}

	void GameObject::destroy() {
		removeAllComponents();
	}

	void GameObject::read(const rapidjson::Value& value) {
		json::get(value, "name", name);
		json::get(value, "tag", tag);

		bool transient = flags[eFlags::TRANSIENT];
		json::get(value, "transient", transient);
		flags[eFlags::TRANSIENT] = transient;

		json::get(value, "position", transform.position);
		json::get(value, "scale", transform.scale);
		json::get(value, "angle", transform.angle);

		json::get(value, "lifetime", lifetime);

		if (value.HasMember("Components")) {
			const rapidjson::Value& componentsValue = value["Components"];
			if (componentsValue.IsArray()) {
				ReadComponents(componentsValue);
			}
		}
	}

	void GameObject::ReadComponents(const rapidjson::Value& value) {
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			const rapidjson::Value& componentValue = value[i];
			if (componentValue.IsObject()) {
				std::string typeName;
				json::get(componentValue, "type", typeName);
				Component* component = ObjectFactory::instance().Create<Component>(typeName);

				if (component) {
					component->create(this);
					component->read(componentValue);
					components.push_back(component);
				}
			}
		}
	}

	void GameObject::update() {
		for (auto c : components) {
			c->update();
		}

		if (flags[eFlags::TRANSIENT]) {
			lifetime -= engine->getTimer().deltaTime();
			if (lifetime <= 0) {
				flags[eFlags::DESTROY] = true;
			}
		}
	}

	void GameObject::draw() {
		RenderComponent* rc = getComponent<RenderComponent>();
		if (rc) {
			rc->draw();
		}
	}

	void GameObject::beginContact(GameObject* other) {
		contacts.push_back(other);

		Event event;
		event.sender = other;
		event.reciever = this;
		event.type = "CollisionEnter";

		EventManager::instance().notify(event);
	}

	void GameObject::endContact(GameObject* other) {
		contacts.remove(other);


		Event event;
		event.sender = other;
		event.reciever = this;
		event.type = "CollisionExit";

		EventManager::instance().notify(event);
	}

	std::vector<GameObject*> GameObject::getContactsWithTag(const std::string& tag) {
		std::vector<GameObject*> _contacts;

		for (auto contact : contacts) {
			if (contact->tag == tag) {
				_contacts.push_back(contact);
			}
		}
		
		return _contacts;
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
