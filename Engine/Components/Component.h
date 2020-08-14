#pragma once
#include "Objects/GameObject.h"

namespace ew {
	class Component : public Object{
	public:
		
		virtual void update() = 0;

		friend class GameObject;

	protected:
		GameObject* owner{ nullptr };
	};
}