#include "pch.h"
#include "RigidBodyComponent.h"

namespace ew {
	void RigidBodyComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void RigidBodyComponent::destroy() {
		owner->engine->getSystem<PhysicsSystem>()->destroyBody(body);
	}

	void RigidBodyComponent::read(const rapidjson::Value& value) {
		json::get(value, "isDynamic", data.isDynamic);
		json::get(value, "isSensor", data.isSensor);
		json::get(value, "lockAngle", data.lockAngle);
		json::get(value, "size", data.size);
		json::get(value, "density", data.density);
		json::get(value, "friction", data.friction);
		json::get(value, "restitution", data.restitution);
	}

	void RigidBodyComponent::update() {
		if (!body) {
			body = owner->engine->getSystem<PhysicsSystem>()->createBody(owner->transform.position, owner->transform.angle, data, owner);
		}

		owner->transform.position = PhysicsSystem::worldToScreen(body->GetPosition());
		owner->transform.angle = ew::radiansToDregrees(body->GetAngle());

		velocity = body->GetLinearVelocity();
		velocity.x = ew::clamp(velocity.x, -5.0f, 5.0f);
		body->SetLinearVelocity(velocity);
	}

	void RigidBodyComponent::setForce(const Vector2& _force) {
		body->ApplyForceToCenter(_force, true);
		//body->SetGravityScale(2.0f); increases gravity
		//body->SetLinearDamping(15.0f); slows movement
	}


}

