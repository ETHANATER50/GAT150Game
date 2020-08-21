#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

namespace ew {
	bool Texture::create(const std::string& name, void* _renderer) {
		renderer = static_cast<Renderer*>(_renderer)->renderer;
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}

	void Texture::destroy() {
		SDL_DestroyTexture(texture);
	}

	void Texture::draw(const Vector2& position, float angle, const Vector2& scale, const Vector2& origin) {
		Vector2 size = getSize();
		size *= scale;
		Vector2 newPos = position - size * origin;

		SDL_Rect rect;
		rect.x = static_cast<int>(newPos.x);
		rect.y = static_cast<int>(newPos.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);
		SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
	}
	void Texture::draw(const SDL_Rect& source, const Vector2& position, float angle, const Vector2& scale, const Vector2& origin) {
		Vector2 size = { source.w, source.h };
		size *= scale;
		Vector2 newPos = position - size * origin;

		SDL_Rect rect;
		rect.x = static_cast<int>(newPos.x);
		rect.y = static_cast<int>(newPos.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);
		SDL_RenderCopyEx(renderer, texture, &source, &rect, angle, NULL, SDL_FLIP_NONE);
	}
	Vector2 Texture::getSize() {
		SDL_Point point;
		SDL_QueryTexture(texture, NULL, NULL, &point.x, &point.y);

		return { point.x, point.y };
	}
}

