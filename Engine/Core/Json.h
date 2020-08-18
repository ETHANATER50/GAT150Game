#pragma once
#include "document.h"
#include <string>

namespace ew {
	namespace json {
		bool load(const std::string& filename, rapidjson::Document& document);
		bool get(const rapidjson::Value& value, const std::string& name, int& data);
		bool get(const rapidjson::Value& value, const std::string& name, float& data);
		bool get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool get(const rapidjson::Value& value, const std::string& name, Vector2& data);
		bool get(const rapidjson::Value& value, const std::string& name, Color& data);
		bool get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data);
	}
}