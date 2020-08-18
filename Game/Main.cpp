#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Objects/ObjectFactory.h"
#include "Core/Json.h"


ew::Engine engine;
ew::GameObject player;

int main(int, char**) {


	rapidjson::Document document; 
	ew::json::load("json.txt", document); 

	std::string str; 
	ew::json::get(document, "string", str); 
	std::cout << str << std::endl; 
	
	bool b; ew::json::get(document, "bool", b); 
	std::cout << b << std::endl; 
	
	int i1; 
	ew::json::get(document, "integer1", i1); 
	std::cout << i1 << std::endl; 
	
	int i2; 
	ew::json::get(document, "integer2", i2); 
	std::cout << i2 << std::endl; 
	
	float f; 
	ew::json::get(document, "float", f); 
	std::cout << f << std::endl; 
	
	ew::Vector2 v2; 
	ew::json::get(document, "vector2", v2); 
	std::cout << v2 << std::endl; 
	ew::Color color; 
	ew::json::get(document, "color", color); 
	std::cout << color << std::endl;

	engine.startup();


	ew::ObjectFactory::instance().initialize();
	ew::ObjectFactory::instance().Register("PlayerComponent", ew::Object::instantiate < ew::PlayerComponent>);

	ew::GameObject* player = ew::ObjectFactory::instance().Create<ew::GameObject>("GameObject");


	player->create(&engine);
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
	player->addComponent(component);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	ew::Texture* background = engine.getSystem<ew::ResourceManager>()->get<ew::Texture>("background.png", engine.getSystem<ew::Renderer>());
	
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
		player->update();

		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_ESCAPE) == ew::InputSystem::ButtonState::PRESSED) {
			quit = true;
		}

		//SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
		engine.getSystem<ew::Renderer>()->beginFrame();


		background->draw({ 0, 0 });
		player->draw();

		engine.getSystem<ew::Renderer>()->endFrame();
	}

	engine.shutdown();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

