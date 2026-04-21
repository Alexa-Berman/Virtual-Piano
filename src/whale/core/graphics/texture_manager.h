#pragma once

#include "exception.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <cstdint>
#include <filesystem>
#include <vector>

namespace whale
{
	struct texture_data
	{
		int width, height, channels;
		uint8_t* data;
		texture_data(int width, int height, int channels, uint8_t* data)
			: width(width), height(height), channels(channels), data(data) {}
		texture_data(texture_data&) = delete;
		void operator=(const texture_data&) = delete;
		~texture_data() { stbi_image_free(data); }
	};

	class texture_manager
	{
	public:
		[[nodiscard]] texture_data load(const std::filesystem::path& path);

		[[nodiscard]] GLuint load_cubemap(const std::vector<std::filesystem::path>& files)
		{
			if (files.size() != 6)
				throw exception("Invalid cubemap size");

			GLuint tex;
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
			for (int face = 0; face < 6; face++)
			{
				auto data = load(files[face]);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_SRGB8, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			return tex;
		}
	};
}