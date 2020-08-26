#include "pch.h"
#include "RigidBodyComponent.h"

namespace ew {
	void RigidBodyComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void RigidBodyComponent::destroy() {

	}

	void RigidBodyComponent::read(const rapidjson::Value& value) {
		json::get(value, "isDynamic", data.isDynamic);
		json::get(value, "lockAngle", data.lockAngle);
		json::get(value, "size", data.size);
		json::get(value, "density", data.density);
		json::get(value, "friction", data.friction);
		json::get(value, "restitution", data.restitution);
	}

	void RigidBodyComponent::update() {
		if (!body) {
			body = owner->engine->getSystem<PhysicsSystem>()->createBody(owner->transform.position, data, owner);
		}

		owner->transform.position = body->GetPosition();
		owner->transform.angle = body->GetAngle();
	}

	void RigidBodyComponent::setForce(const Vector2& _force) {
		body->ApplyLinearImpulseToCenter(_force, true);
	}


}

