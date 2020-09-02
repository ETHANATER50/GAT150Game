#include "pch.h"
#include "EnemyComponent.h"
#include "Objects/Scene.h"
#include "Components/PhysicsComponent.h"

namespace ew {

	void EnemyComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void EnemyComponent::destroy() {

	}

	void EnemyComponent::update() {
		GameObject* player = owner->scene->find("Player");
		if (player) {
			Vector2 direction = player->transform.position - owner->transform.position;
			Vector2 force = direction.normalized() * 10.0f;

			PhysicsComponent* physicsComponent = owner->getComponent<PhysicsComponent>();
			physicsComponent->applyForce(force);
		}
	}

}

