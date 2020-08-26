#pragma once
#include "Components/PhysicsComponent.h"

namespace ew {
	class RigidBodyComponent : public PhysicsComponent {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual RigidBodyComponent* clone() const override { return new RigidBodyComponent{ *this }; }

		void read(const rapidjson::Value& value) override;

		virtual void update() override;

		virtual void setForce(const Vector2& _force)override;

	protected:
		b2Body* body{ nullptr };
		PhysicsSystem::RigidBodyData data;
	};
}