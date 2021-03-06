#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <bitset>
#include <list>

namespace ew {
	class Component;

	class GameObject : public Object {
	public:
		enum  eFlags {
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};

	public:

		GameObject() = default;
		GameObject(const GameObject& other);

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual Object* clone() const override { return new GameObject{ *this }; }

		void read(const rapidjson::Value& value) override;
		void ReadComponents(const rapidjson::Value& value);

		void update();
		void draw();

		void beginContact(GameObject* other);
		void endContact(GameObject* other);
		std::vector<GameObject*> getContactsWithTag(const std::string& tag);

		template<typename T>
		T* getComponent();

		void addComponent(Component* c);
		void removeComponent(Component* c);
		void removeAllComponents();

	public:
		Transform transform;
		Engine* engine{ nullptr };
		class Scene* scene{ nullptr };

		std::string name;
		std::string tag;
		std::bitset<32> flags;

		float lifetime{ 0 };

	protected:
		std::vector<Component*> components;
		std::list<GameObject*> contacts;

	};

	template<typename T>
	T* GameObject::getComponent() {
		T* result{ nullptr };
		for (auto component : components) {
			result = dynamic_cast<T*>(component);
			if (result) break;
		}
		return result;
	}

}