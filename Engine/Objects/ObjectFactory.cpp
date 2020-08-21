#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"


namespace ew {
	void ew::ObjectFactoryImpl::initialize() {
		ew::ObjectFactory::instance().Register("GameObject", ew::Object::instantiate<ew::GameObject>);
		ew::ObjectFactory::instance().Register("PhysicsComponent", ew::Object::instantiate < ew::PhysicsComponent>);
		ew::ObjectFactory::instance().Register("SpriteComponent", ew::Object::instantiate < ew::SpriteComponent>);
		ew::ObjectFactory::instance().Register("SpriteAnimationComponent", ew::Object::instantiate < ew::SpriteAnimationComponent>);
	}

}
