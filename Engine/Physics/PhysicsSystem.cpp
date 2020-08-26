#include "pch.h"
#include "PhysicsSystem.h"
#include "ContactListener.h"

namespace ew {
	bool PhysicsSystem::startup() {
		b2Vec2 gravity{ 0, 150 };
		world = new b2World(gravity);
		contactListener = new ContactListener;
		world->SetContactListener(contactListener);
		return true;
	}

	void PhysicsSystem::shutdown() {
		delete world;
		world = nullptr;
		delete contactListener;
		contactListener = nullptr;
	}

	b2Body* PhysicsSystem::createBody(const Vector2& position, const Vector2& size, float density, bool isDynamic) {
		b2BodyDef bodyDef;

		bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(position.x, position.y);
		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(size.x, size.y);

		body->CreateFixture(&shape, density);

		return body;
	}

	b2Body* PhysicsSystem::createBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameObject) {
		b2BodyDef bodyDef;

		bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.angle = ew::degreesToRadians(angle);
		bodyDef.fixedRotation = data.lockAngle;
		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(data.size.x, data.size.y);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.shape = &shape;
		fixtureDef.userData = gameObject;
		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::update() {
		float timeStep{ 1.0f / 60.0f };
		world->Step(timeStep, 8, 3);
	}

}

