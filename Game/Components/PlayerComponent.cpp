#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"


namespace ew {
	void PlayerComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void PlayerComponent::destroy() {

	}

	void PlayerComponent::update() {
		auto contacts = owner->getContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		ew::Vector2 force{ 0, 0 };
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_A) == ew::InputSystem::ButtonState::HELD) {
			force.x = -80;
		}
		if (owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_D) == ew::InputSystem::ButtonState::HELD) {
			force.x = 80;
		}

		if (onGround && owner->engine->getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_SPACE) == ew::InputSystem::ButtonState::PRESSED) {
			force.y = -700;
			AudioComponent* audioComponent = owner->getComponent<AudioComponent>(); 
			if (audioComponent) { 
				audioComponent->play(); 
			}
		}

		PhysicsComponent* component = owner->getComponent<PhysicsComponent>();
		if (component) {
			component->setForce(force);
		}

		auto coinContacts = owner->getContactsWithTag("Coin");

		for (auto contact : coinContacts) {
			contact->flags[GameObject::eFlags::DESTROY] = true;
		}
	}

}
