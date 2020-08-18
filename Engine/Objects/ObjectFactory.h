#pragma once
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Object.h"

namespace ew {
	class ObjectFactoryImpl : public Factory<Object, std::string> {
	public:
	public:
		void initialize();
	};

	class ObjectFactory : public Singleton<ObjectFactoryImpl> {
	
	private:
		ObjectFactory() {}
	};
}