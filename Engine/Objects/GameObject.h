#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"

namespace ew {
	class Component;

	class GameObject : public Object {
	public:


		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;

		void update();
		void draw();

		template<typename T>
		T* getComponent();

		void addComponent(Component* c);
		void removeComponent(Component* c);
		void removeAllComponents();

	public:
		Transform transform;
		Engine* engine;

	protected:
		std::vector<Component*> components;

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