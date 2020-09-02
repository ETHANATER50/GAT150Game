#pragma once
#include "Components/Component.h"

namespace ew {
	class EnemyComponent : public Component {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual Object* clone() const override { return new EnemyComponent{ *this }; }

		virtual void update() override;

	};
}