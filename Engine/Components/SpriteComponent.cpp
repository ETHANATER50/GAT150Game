#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace ew {
	void SpriteComponent::create(void* data) {
		texture = owner->engine->getSystem<ew::ResourceManager>()->get<ew::Texture>("cars.png", owner->engine->getSystem<ew::Renderer>());

	}

	void SpriteComponent::destroy() {

	}

	void SpriteComponent::update() {

	}

	void SpriteComponent::draw() {
		texture->draw({ 125, 440, 60, 110 }, owner->transform.position, { 1, 1 }, owner->transform.angle);
	}

}

