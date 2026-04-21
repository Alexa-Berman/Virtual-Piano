#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace whale
{
	constexpr uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		return (r << 24) |
		       (g << 16) |
			   (b << 8)  |
			   (a);
	}

	constexpr uint32_t rgba(uint8_t r, uint8_t g, uint8_t b)
	{
		return rgba(r, g, b, 255);
	}

	constexpr uint32_t rgba(uint32_t hex)
	{
		return rgba(
			(hex >> 16) & 0xFF,
			(hex >> 8)  & 0xFF,
			(hex)       & 0xFF
		);
	}

	constexpr glm::vec4 srgba_vec4(uint32_t hex, float gamma)
	{
		return glm::vec4(std::pow(static_cast<float>((hex >> 16) & 0xFF) / 255.0f, gamma),
						 std::pow(static_cast<float>((hex >> 8) & 0xFF) / 255.0f, gamma),
						 std::pow(static_cast<float>((hex) & 0xFF) / 255.0f, gamma),
						 1.0f);
	}
}