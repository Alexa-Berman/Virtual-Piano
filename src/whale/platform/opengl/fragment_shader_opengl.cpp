#include "fragment_shader.h"

namespace whale
{
	fragment_shader::fragment_shader(const std::string& source)
		: basic_shader(source)
	{
		handle = glCreateShader(GL_FRAGMENT_SHADER);
		const char* p_source = source.c_str();
		glShaderSource(handle, 1, &p_source, nullptr);
		glCompileShader(handle);

		check_status();
	}
}