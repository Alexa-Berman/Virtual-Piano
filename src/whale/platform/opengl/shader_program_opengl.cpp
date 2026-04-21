#include "shader_program_opengl.h"

#include "exception.h"

#include <glm/gtc/type_ptr.hpp>

#include <format>

namespace whale
{
	shader_program::~shader_program()
	{
		glDeleteProgram(program);
	}

	void shader_program::use()
	{
		glUseProgram(program);
	}

	void shader_program::set_uniform(int location, float x, float y, float z, float w) const
	{
		glProgramUniform4f(program, location, x, y, z, w);
	}

	void shader_program::set_uniform(int location, const glm::vec4& v) const
	{
		set_uniform(location, v.x, v.y, v.z, v.w);
	}

	void shader_program::set_uniform(int location, float x, float y) const
	{
		glProgramUniform2f(program, location, x, y);
	}

	void shader_program::set_uniform(int location, glm::vec2 v) const
	{
		set_uniform(location, v.x, v.y);
	}

	void shader_program::set_uniform(int location, const glm::mat4& m) const
	{
		glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, glm::value_ptr(m));
	}

	void shader_program::set_uniform(int location, float x, float y, float z) const
	{
		glProgramUniform3f(program, location, x, y, z);
	}

	void shader_program::set_uniform(int location, const glm::vec3& v) const
	{
		set_uniform(location, v.x, v.y, v.z);
	}

	void shader_program::set_uniform(int location, float s) const
	{
		glProgramUniform1f(program, location, s);
	}

	void shader_program::set_uniform(int location, int i) const
	{
		glProgramUniform1i(program, location, i);
	}

	void shader_program::set_uniform(int location, unsigned int i) const
	{
		glProgramUniform1ui(program, location, i);
	}

	void shader_program::set_uniform(int location, uint64_t i) const
	{
		// This crashes on low power mode on my laptop for some reason LOL
		// beware of this
		//glProgramUniform1ui64ARB(program, location, i);
	}

	void shader_program::set_uniform(int location, const glm::vec4* vec_arr, size_t count) const
	{
		glProgramUniform4fv(program, location, static_cast<int>(count), reinterpret_cast<const float*>(vec_arr));
	}

	void shader_program::set_uniform(int location, const float* float_array, size_t count) const
	{
		glProgramUniform1fv(program, location, count, float_array);
	}

	void shader_program::check_status() const
	{
		char info[512];
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, nullptr, info);
			throw exception(std::format("Failed to link shader program: {}", info));
		}
	}
}