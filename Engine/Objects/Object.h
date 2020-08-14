#pragma once

namespace ew {
	class Object {
	public:

		virtual void create(void* data = nullptr) = 0;
		virtual void destroy() = 0;
	};
}