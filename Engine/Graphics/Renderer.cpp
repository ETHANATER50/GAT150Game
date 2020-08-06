#include "pch.h"
#include "Renderer.h"

namespace ew {
	bool Renderer::startup() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}

	void Renderer::shutdown() {
	}

	void Renderer::update() {
	}
	bool Renderer::create(const std::string& name, int width, int height)
	{
		window = SDL_CreateWindow(name.c_str() , 100, 100, width, height, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cout << "Error. " << SDL_GetError() << std::endl;
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer == nullptr) {
			std::cout << "Error. " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}
	void Renderer::beginFrame() {
		SDL_RenderClear(renderer);
	}
	void Renderer::endFrame() {
		SDL_RenderPresent(renderer);
	}
}

