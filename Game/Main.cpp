#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "Core/Json.h"


ew::Engine engine;
ew::GameObject player;
ew::Scene scene;

int main(int, char**) {
	
	engine.startup();
	scene.create(&engine);

	ew::ObjectFactory::instance().initialize();
	ew::ObjectFactory::instance().Register("PlayerComponent", ew::Object::instantiate < ew::PlayerComponent>);

	ew::GameObject* player = ew::ObjectFactory::instance().Create<ew::GameObject>("GameObject");

	rapidjson::Document document; 
	ew::json::load("scene.txt", document);
	scene.read(document);

	/*player->create(&engine);
	ew::json::load("player.txt", document);
	player->read(document);

	ew::Component* component;
	component = ew::ObjectFactory::instance().Create<ew::Component>("PhysicsComponent");
	component->create(player);
	player->addComponent(component);

	component = ew::ObjectFactory::instance().Create<ew::Component>("SpriteComponent");
	component->create(player);
	ew::json::load("sprite.txt", document);
	component->read(document);
	player->addComponent(component);

	component = ew::ObjectFactory::instance().Create<ew::Component>("PlayerComponent");
	component->create(player);
	player->addComponent(component);*/

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//ew::Texture* background = engine.getSystem<ew::ResourceManager>()->get<ew::Texture>("background.png", engine.getSystem<ew::Renderer>());
	
	ew::Vector2 velocity{ 0,0 };

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
	//	player->update();

		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_ESCAPE) == ew::InputSystem::ButtonState::PRESSED) {
			quit = true;
		}

		//SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
		engine.getSystem<ew::Renderer>()->beginFrame();


		//background->draw({ 0, 0 });
		scene.draw();
		//player->draw();

		engine.getSystem<ew::Renderer>()->endFrame();
	}

	scene.destroy();
	engine.shutdown();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

