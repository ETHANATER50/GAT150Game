#pragma once
#include "Component.h"

namespace ew {
	class RenderComponent : public Component {
	public:
		virtual void draw() = 0;
	};
}