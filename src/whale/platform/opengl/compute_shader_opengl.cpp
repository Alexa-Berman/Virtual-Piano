#include "compute_shader.h"

namespace whale
{
	compute_shader::compute_shader(const std::string& source)
		: basic_shader(source)
	{
		handle = glCreateShader(GL_COMPUTE_SHADER);
		const char* p_source = source.c_str();
		glShaderSource(handle, 1, &p_source, nullptr);
		glCompileShader(handle);

		check_status();
	}
}