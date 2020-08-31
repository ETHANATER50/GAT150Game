#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "Core/Json.h"
#include "TileMap.h"


ew::Engine engine;
ew::GameObject player;
ew::Scene scene;

int main(int, char**) {
	
	engine.startup();
	scene.create(&engine);

	ew::ObjectFactory::instance().initialize();
	ew::ObjectFactory::instance().Register("PlayerComponent", new ew::Creator<ew::PlayerComponent, ew::Object>);

	ew::GameObject* player = ew::ObjectFactory::instance().Create<ew::GameObject>("GameObject");

	rapidjson::Document document; 
	ew::json::load("scene.txt", document);
	scene.read(document);

	ew::TileMap tileMap;
	ew::json::load("tilemap.txt", document);
	tileMap.read(document);
	tileMap.create(&scene);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.update();
		scene.update();

		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_ESCAPE) == ew::InputSystem::ButtonState::PRESSED) {
			quit = true;
		}

		engine.getSystem<ew::Renderer>()->beginFrame();

		scene.draw();

		engine.getSystem<ew::Renderer>()->endFrame();
	}

	scene.destroy();
	engine.shutdown();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

