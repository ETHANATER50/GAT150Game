#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"


namespace ew {
	void PlayerComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
		EventManager::instance().subscribe("CollisionEnter", std::bind(&PlayerComponent::onCollisionEnter, this, std::placeholders::_1), owner);
		EventManager::instance().subscribe("CollisionExit", std::bind(&PlayerComponent::onCollisionExit, this, std::placeholders::_1), owner);

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
			force.y = -2500;
			AudioComponent* audioComponent = owner->getComponent<AudioComponent>(); 
			if (audioComponent) { 
				audioComponent->setSoundName("sounds/jump.wav");
				audioComponent->play();
			}
		}

		PhysicsComponent* component = owner->getComponent<PhysicsComponent>();
		if (component) {
			Vector2 velocity = component->getVelocity();

			component->applyForce(force);

			SpriteComponent* sprite = owner->getComponent<SpriteComponent>();

			if (velocity.x > 0.1f) sprite->flip(false);
			if (velocity.x < -0.1f) sprite->flip(true);

			
		}

		auto enemyContacts = owner->getContactsWithTag("Enemy");

		if (!enemyContacts.empty()) std::cout << "enemy hit\n";
	}

	void PlayerComponent::onCollisionEnter(const Event& event) {
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		if (gameObject->tag == "Enemy") {
			AudioComponent* audio = owner->getComponent<AudioComponent>();
			audio->setSoundName("Sounds/grunt.wav");
			audio->play();

			owner->flags[GameObject::eFlags::DESTROY] = true;

			Event event;
			event.type = "PlayerDead";
			int score = 300;
			event.data = &score;
			EventManager::instance().notify(event);
		}
		if (gameObject->tag == "Coin") {
			AudioComponent* audio = owner->getComponent<AudioComponent>();
			audio->setSoundName("sounds/coin.wav");
			audio->play();

			gameObject->flags[GameObject::eFlags::DESTROY] = true;
		}
	}

	void PlayerComponent::onCollisionExit(const Event& event)  {
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		std::cout << "collision exit: " << gameObject->name << std::endl;
	}

}
