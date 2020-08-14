#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"


namespace ew {
	void PlayerComponent::create(void* data) {

	}

	void PlayerComponent::destroy() {

	}

	void PlayerComponent::update() {
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_A) == ew::InputSystem::ButtonState::HELD) {
			owner->transform.angle -= 200.0f * owner->engine->getTimer().deltaTime();
		}
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_D) == ew::InputSystem::ButtonState::HELD) {
			owner->transform.angle += 200.0f * owner->engine->getTimer().deltaTime();
		}

		ew::Vector2 force{ 0, 0 };
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_S) == ew::InputSystem::ButtonState::HELD) {
			force = ew::Vector2::down * 1000.0f;
		}
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_W) == ew::InputSystem::ButtonState::HELD) {
			force = ew::Vector2::forward * 1000.0f;
		}
		force = ew::Vector2::rotate(force, ew::degreesToRadians(owner->transform.angle));

		PhysicsComponent* component = owner->getComponent<PhysicsComponent>();
		if (component) {
			component->setForce(force);
		}
	}

}
