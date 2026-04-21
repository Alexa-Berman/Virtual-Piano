#pragma once

#include "basic_shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstdint>

namespace whale
{
	class shader_program
	{
	private:
		template <typename T>
		void attach_shader(T&& shader)
		{
			if constexpr (is_shader<T>)
			{
				glAttachShader(program, std::forward<T>(shader).handle);
			}
			else if constexpr (is_shader_ptr<T>)
			{
				glAttachShader(program, std::forward<T>(shader)->handle);
			}
			else
			{
				static_assert("Invalid argument to shader program");
			}
		}

	public:
		shader_program() = default;

		template <typename... Args>
		shader_program(Args&&... shaders)
			: program(glCreateProgram())
		{
			(attach_shader(std::forward<Args>(shaders)), ...);
			glLinkProgram(program);
			check_status();
		}

		~shader_program();

		shader_program(shader_program&) = delete;

		// TODO: Add move constructor this has caused subtle bugs with opengl state stuff

		GLint handle() const
		{
			return program;
		}

		void use();

		void set_uniform(int location, float x, float y, float z, float w) const;
		void set_uniform(int location, const glm::vec4& v) const;
		void set_uniform(int location, float x, float y) const;
		void set_uniform(int location, glm::vec2 v) const;
		void set_uniform(int location, const glm::mat4& m) const;
		void set_uniform(int location, float x, float y, float z) const;
		void set_uniform(int location, const glm::vec3& v) const;
		void set_uniform(int location, float s) const;
		void set_uniform(int location, int i) const;
		void set_uniform(int location, unsigned int i) const;
		void set_uniform(int location, uint64_t i) const;
		void set_uniform(int location, const glm::vec4* vec_arr, size_t count) const;
		void set_uniform(int location, const float* float_array, size_t count) const;

	private:
		GLuint program;

		void check_status() const;
	};
}
