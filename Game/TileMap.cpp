#include "pch.h"
#include "TileMap.h"
#include "Objects/ObjectFactory.h"
#include "Objects/GameObject.h"
#include"Objects/Scene.h"

namespace ew {
	void TileMap::read(const rapidjson::Value& value) {
		json::get(value, "numX", numX);
		json::get(value, "numY", numY);
		json::get(value, "size", size);
		json::get(value, "start", start);

		json::get(value, "tileNames", tileNames);
		json::get(value, "tiles", tiles);
	}

	bool TileMap::create(Scene* scene) {

		for (size_t i = 0; i < tiles.size(); i++) {
			int index = tiles[i];
			if (index != 0) {
				GameObject* gameObject = ObjectFactory::instance().Create<GameObject>(tileNames[index]);
				float x = i % numX;
				float y = i / numX;
				gameObject->transform.position = start + ew::Vector2{ x, y } * size;

				scene->addGameObject(gameObject);
			}
		}

		return true;
	}

}

