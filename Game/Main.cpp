#include "Graphics/Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


int main(int, char**) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "Error. " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Error. " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	int width = 128;
	int height = 128;
	SDL_Texture* texture2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[width * height];
	memset(pixels, 255, width * height * sizeof(Uint32));
	SDL_UpdateTexture(texture2, NULL, pixels, width * sizeof(Uint32));

	ew::Texture texture;
	texture.create("sf2.png", renderer);
	float angle{ 0 };

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
		SDL_RenderClear(renderer);

		for (int i = 0; i < width * height; i++) {
			Uint8 c1 = rand() % 256;
			Uint8 c2 = rand() % 256;
			Uint8 c3 = rand() % 256;
			pixels[i] = (c1 << 24 | c2 << 16 | c3 << 8);
		}
		SDL_UpdateTexture(texture2, NULL, pixels, width * sizeof(Uint32));

		SDL_Rect rect;
		rect.x = 40;
		rect.y = 40;
		rect.w = width;
		rect.h = height;
		SDL_RenderCopy(renderer, texture2, NULL, NULL);

		angle += 1;

		texture.draw({ 500, 100 }, { 2, 2 }, angle);

		SDL_RenderPresent(renderer);
	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}

