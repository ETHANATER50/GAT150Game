#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"


namespace ew {
	void ew::ObjectFactoryImpl::initialize() {
		ew::ObjectFactory::instance().Register("GameObject", new Creator<GameObject, Object>);
		ew::ObjectFactory::instance().Register("PhysicsComponent", new Creator<PhysicsComponent, Object>);
		ew::ObjectFactory::instance().Register("SpriteComponent", new Creator<SpriteComponent, Object>);
		ew::ObjectFactory::instance().Register("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
		ew::ObjectFactory::instance().Register("RigidBodyComponent", new Creator<RigidBodyComponent, Object>);
		ew::ObjectFactory::instance().Register("AudioComponent", new Creator<AudioComponent, Object>);
	}

}
