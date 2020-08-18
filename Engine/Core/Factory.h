#pragma once
#include <map>
#include <functional>

namespace ew {
	template<typename Base, typename Key>
	class Factory {
	public:
		using function_t = std::function<Base* ()>;

		template<typename T = Base>
		T* Create(Key key);
		void Register(Key key, function_t function);

	protected:
		std::map<Key, function_t> registry;
	};


	template<typename Base, typename Key>
	template<typename T>
	inline T* Factory<Base, Key>::Create(Key key) {
		T* object{ nullptr };

		auto iter = registry.find(key);
		if (iter  != registry.end()) {
			object = dynamic_cast<T*>(iter->second());
		}
		return object;
	}
	template<typename Base, typename Key>
	inline void Factory<Base, Key>::Register(Key key, function_t function) {
		registry[key] = function;
	}
}