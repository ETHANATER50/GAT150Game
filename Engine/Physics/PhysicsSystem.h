#pragma once
#include "Core/System.h"
#include "box2d/box2d.h"

namespace ew {
	class GameObject;

	class PhysicsSystem : public System {
	public:
		struct RigidBodyData {
			Vector2 size;
			float density{ 0 };
			float friction{ 1 };
			float restitution{ 0.3f };
			bool lockAngle{ false };
			bool isDynamic{ false };
		};


	public:
		virtual bool startup() override;
		virtual void shutdown() override;

		virtual b2Body* createBody(const Vector2& position, const Vector2& size, float density, bool isDynamic = true);
		virtual b2Body* createBody(const Vector2& position, const RigidBodyData& data, GameObject* owner = nullptr);

		virtual void update() override;



	protected:
		b2World* world{ nullptr };
	};
}