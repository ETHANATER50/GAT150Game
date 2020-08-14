#pragma once
#include "Components/Component.h"

namespace ew {
	class PlayerComponent : public Component{
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;

		virtual void update() override;

	};
}