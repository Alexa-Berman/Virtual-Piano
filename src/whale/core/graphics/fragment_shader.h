#pragma once

#include "basic_shader.h"

namespace whale
{
	class fragment_shader : public basic_shader
	{
	public:
		fragment_shader(const std::string& source);
		virtual ~fragment_shader() = default;
	};
}
