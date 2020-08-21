#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace ew {
	void SpriteComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
		//ASSERT_MSG(texture != nullptr, "Error texture " + textureName + " not loaded");
	}

	void SpriteComponent::destroy() {

	}

	void SpriteComponent::read(const rapidjson::Value& value) {
		json::get(value, "texture", textureName);
		json::get(value, "origin", origin);
		json::get(value, "rect", rect);
		
	}

	void SpriteComponent::update() {

	}

	void SpriteComponent::draw() {
		//{ 125, 440, 60, 110 }
		Texture* texture = owner->engine->getSystem<ew::ResourceManager>()->get<ew::Texture>(textureName, owner->engine->getSystem<ew::Renderer>());
		texture->draw(rect, owner->transform.position, owner->transform.angle, ew::Vector2::one * owner->transform.scale, origin);
	}

}

