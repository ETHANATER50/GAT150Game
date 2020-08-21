#include "pch.h"
#include "SpriteAnimationComponent.h"
#include "Graphics/Texture.h"

namespace ew {
	void SpriteAnimationComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void SpriteAnimationComponent::destroy() {

	}

	void SpriteAnimationComponent::read(const rapidjson::Value& value) {
		SpriteComponent::read(value);

		json::get(value, "numX", numX);
		json::get(value, "numY", numY);
		json::get(value, "frames", frames);
		json::get(value, "fps", fps);

		frameRate = 1.0f / fps;
	}

	void SpriteAnimationComponent::update() {
		frameTimer += owner->engine->getTimer().deltaTime();
		if (frameTimer >= frameRate) {
			frameTimer = 0;
			frame++;
			if (frame >= frames) {
				frame = 0;
			}
		}

		Texture* texture = owner->engine->getSystem<ew::ResourceManager>()->get<ew::Texture>(textureName, owner->engine->getSystem<ew::Renderer>());
		Vector2 textureSize = texture->getSize();

		Vector2 cellCount{ numX, numY };
		Vector2 cellSize = textureSize / cellCount;

		rect.x = static_cast<int>((frame % numX) * cellSize.x);
		rect.y = static_cast<int>((frame / numY) * cellSize.y);
		rect.w = static_cast<int>(cellSize.x);
		rect.h = static_cast<int>(cellSize.y);
	}

}

