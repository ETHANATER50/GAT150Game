#include "pch.h"
#include "PhysicsComponent.h"
#include "Objects/GameObject.h"

namespace ew {
	void PhysicsComponent::create(void* data) {
		drag = 0.95f;
	}

	void PhysicsComponent::destroy() {

	}

	void PhysicsComponent::update() {
		velocity += force * owner->engine->getTimer().deltaTime();
		velocity *= drag;
		owner->transform.position += velocity * owner->engine->getTimer().deltaTime();;
	}

}
