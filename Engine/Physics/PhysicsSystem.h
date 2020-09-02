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
			float gravityScale{ 1.0f };
			bool lockAngle{ false };
			bool isDynamic{ false };
			bool isSensor{ false };
		};


	public:
		virtual bool startup() override;
		virtual void shutdown() override;

		virtual void update() override;

		virtual b2Body* createBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* owner = nullptr);
		void destroyBody(b2Body* body);

		static Vector2 worldToScreen(const Vector2& world) { return world * 32.0f; }
		static Vector2 screenToWorld(const Vector2& screen) { return screen * 0.03125f; }

	protected:
		b2World* world{ nullptr };
		class ContactListener* contactListener{ nullptr };
	};
}