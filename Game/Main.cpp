#include "Graphics/Texture.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

ew::Renderer renderer;
ew::ResourceManager resourceManager;
ew::InputSystem inputSystem;

int main(int, char**) {

	renderer.startup();
	resourceManager.startup();
	inputSystem.startup();


	renderer.create("GAT150", 800, 600);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	ew::Texture* texture = resourceManager.get<ew::Texture>("sf2.png", &renderer);
	ew::Texture* texture2 = resourceManager.get<ew::Texture>("sf2.png", &renderer);

	float angle{ 0 };
	ew::Vector2 position{ 400,300 };

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		resourceManager.update();
		inputSystem.update();

		if (inputSystem.getButtonState(SDL_SCANCODE_A) == ew::InputSystem::ButtonState::HELD) {
			position.x -= 10.0f;
		}
		if (inputSystem.getButtonState(SDL_SCANCODE_D) == ew::InputSystem::ButtonState::HELD) {
			position.x += 10.0f;
		}
		if (inputSystem.getButtonState(SDL_SCANCODE_W) == ew::InputSystem::ButtonState::HELD) {
			position.y -= 10.0f;
		}
		if (inputSystem.getButtonState(SDL_SCANCODE_S) == ew::InputSystem::ButtonState::HELD) {
			position.y += 10.0f;
		}

		//SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
		renderer.beginFrame();

		angle += 0.5f;

		texture->draw({ 500, 100 }, { 2, 2 }, angle);
		texture2->draw(position, { 1, 1 }, angle);

		renderer.endFrame();
	}

	resourceManager.shutdown();
	inputSystem.shutdown();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

