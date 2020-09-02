#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace ew {
	class PhysicsComponent : public Component {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual Object* clone() const override { return new PhysicsComponent{ *this }; }

		virtual void update() override;

		virtual void applyForce(const Vector2& _force) { force = _force; }
		virtual Vector2 getVelocity() { return velocity; }

	protected:
		Vector2 velocity{ 0, 0 };
		Vector2 force{ 0,0 };
		float drag{ 1 };
	};
}