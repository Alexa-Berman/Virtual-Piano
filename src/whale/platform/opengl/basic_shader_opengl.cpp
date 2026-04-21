#include "basic_shader.h"

#include "exception.h"

#include <format>
#include <string>

namespace whale
{
	basic_shader::basic_shader(const std::string& source)
		: source(source), handle(0) {}

	basic_shader::~basic_shader() noexcept
	{
		glDeleteShader(handle);
	}

	void basic_shader::check_status() const
	{
		char info[512];
		GLint success;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(handle, 512, nullptr, info);
			throw exception(std::format("Failed to compile shader: {}", info));
		}
	}
}

