#pragma once
#include "Core/Json.h"
#include "Core/EventManager.h"

namespace ew {
	class Object {
	public:

		virtual void create(void* data = nullptr) = 0;
		virtual void destroy() = 0;
		virtual Object* clone() const { return nullptr; }

		virtual void read(const rapidjson::Value& value) {}

		virtual void update() = 0;

		template<typename T>
		static T* instantiate() {
			T* instance = new T;
			return instance;
		}
	};
}