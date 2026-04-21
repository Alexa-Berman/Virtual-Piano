#pragma once

#include "basic_shader.h"

namespace whale
{
	class compute_shader : public basic_shader
	{
	public:
		compute_shader(const std::string& source);
		virtual ~compute_shader() = default;
	};
}
