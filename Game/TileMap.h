#pragma once
#include "Core/Json.h"
#include "Math/Vector2.h"
#include <vector>

namespace ew {
	class TileMap {
	public:

		void read(const rapidjson::Value& value);

		bool create(class Scene* scene);

	protected:
		int numX{ 0 };
		int numY{ 0 };
		Vector2 size;
		Vector2 start;
		std::vector<std::string> tileNames;
		std::vector<int> tiles;
	};
}