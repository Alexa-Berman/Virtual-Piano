#pragma once

#include "basic_shader.h"
#include "exception.h"

#include <glad/glad.h>

#include <filesystem>
#include <memory>
#include <type_traits>
#include <unordered_map>

namespace whale
{
	template <typename T>
	concept contiguous_container = requires(T&& c)
	{
		c.data();
		c.size();
	};

	class shader_manager
	{
	public:
		~shader_manager();

		// Loads a shader based on file extension:
		// .vert, .frag, and .comp supported
		[[nodiscard]] std::unique_ptr<basic_shader> load(const std::filesystem::path& path);

		template <typename T>
		GLuint set_uniform_buffer(int binding, const T& buffer)
		{
			static_assert(std::is_standard_layout_v<T>, "Uniform buffer must be standard layout");

			GLuint ubo;
			if (uniform_buffers.contains(binding))
			{
				ubo = uniform_buffers.at(binding);
				glNamedBufferSubData(ubo, 0, sizeof(T), &buffer);
			}
			else
			{
				glCreateBuffers(1, &ubo);
				glNamedBufferData(ubo, sizeof(T), &buffer, GL_DYNAMIC_DRAW);
				glBindBufferBase(GL_UNIFORM_BUFFER, binding, ubo);
				uniform_buffers.emplace(binding, ubo);
			}
			return ubo;
		}

		template <typename T>
		requires std::is_aggregate_v<T>
		GLuint set_storage_buffer(int binding, const T& buffer)
		{
			GLuint ssbo;
			if (storage_buffers.contains(binding))
			{
				ssbo = storage_buffers.at(binding);
				glNamedBufferSubData(ssbo, 0, sizeof(T), &buffer);
			}
			else
			{
				glCreateBuffers(1, &ssbo);
				glNamedBufferData(ssbo, sizeof(T), &buffer, GL_DYNAMIC_DRAW);
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ssbo);
				storage_buffers.emplace(binding, ssbo);
			}
			return ssbo;
		}

		template <contiguous_container T>
		GLuint set_storage_buffer(int binding, const T& buffer)
		{
			if (buffer.size() == 0)
				throw exception("Input to shader storage buffer is empty");

			GLuint ssbo;
			if (storage_buffers.contains(binding))
			{
				ssbo = storage_buffers.at(binding);
				glNamedBufferSubData(ssbo, 0, buffer.size() * sizeof(buffer[0]), buffer.data());
			}
			else
			{
				glCreateBuffers(1, &ssbo);
				glNamedBufferData(ssbo, sizeof(T), &buffer, GL_DYNAMIC_DRAW);
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ssbo);
				storage_buffers.emplace(binding, ssbo);
			}
			return ssbo;
		}

		// Create an empty ssbo or clear an existing one
		GLuint set_storage_buffer(int binding, uint32_t size)
		{
			GLuint ssbo;
			if (storage_buffers.contains(binding))
			{
				ssbo = storage_buffers.at(binding);
				glNamedBufferData(ssbo, size, nullptr, GL_DYNAMIC_DRAW);
			}
			else
			{
				glCreateBuffers(1, &ssbo);
				glNamedBufferData(ssbo, size, nullptr, GL_DYNAMIC_DRAW);
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ssbo);
				storage_buffers.emplace(binding, ssbo);
			}
			return ssbo;
		}

	private:
		std::unordered_map<int, GLuint> uniform_buffers;
		std::unordered_map<int, GLuint> storage_buffers;

		// Very basic preprocessor that recursively resolves #include directives since glsl doesn't support them natively.
		// I wanted to have shared shader code so this supports that.
		std::string resolve_includes(const std::filesystem::path& current_file);
	};
}

