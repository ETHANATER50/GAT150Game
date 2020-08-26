#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"


namespace ew {
	void PlayerComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void PlayerComponent::destroy() {

	}

	void PlayerComponent::update() {
		ew::Vector2 force{ 0, 0 };

		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_A) == ew::InputSystem::ButtonState::HELD) {
			force.x = -20000;
		}
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_D) == ew::InputSystem::ButtonState::HELD) {
			force.x = 20000;
		}

		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_SPACE) == ew::InputSystem::ButtonState::PRESSED) {
			force.y = -200000000000;
		}

		PhysicsComponent* component = owner->getComponent<PhysicsComponent>();
		if (component) {
			component->setForce(force);
		}
	}

}
