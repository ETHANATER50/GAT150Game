#include "pch.h"
#include "Engine.h"

namespace ew {
	bool Engine::startup() {
		systems.push_back(new Renderer);
		systems.push_back(new ResourceManager);
		systems.push_back(new PhysicsSystem);
		systems.push_back(new InputSystem);

		for (auto system : systems) {
			system->startup();
		}

		getSystem<Renderer>()->create("GAT150", 800, 600);


		return true;
	}

	void Engine::shutdown() {
		for (auto system : systems) {
			system->shutdown();
			delete system;
		}
		systems.clear();
		SDL_Quit();
	}

	void Engine::update() {
		timer.tick();
		for (auto system : systems) {
			system->update();
		}
	}

}
