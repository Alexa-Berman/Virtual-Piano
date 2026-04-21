#pragma once

#include "basic_shader.h"

namespace whale
{
	class vertex_shader : public basic_shader
	{
	public:
		vertex_shader(const std::string& source);
		virtual ~vertex_shader() = default;
	};
}
