#pragma once

#include "basic_camera.h"
#include "shader_manager.h"
#include "shader_program_opengl.h"
#include "triangle_list.h"

#include <filesystem>
#include <memory>
#include <utility>
#include <vector>

namespace whale
{
	class basic_terrain
	{
	public:
		basic_terrain(shader_manager& sm);
		void load_file(const std::filesystem::path& path);

		void render(shader_program& program, basic_camera& cam);

		[[nodiscard]] float get_height(int x, int z) const;

		// Normalized coordinates on the mesh from [0-1] for sampling terrain
		[[nodiscard]] std::pair<glm::vec3, glm::vec3> get_pos_and_normal(float x, float z);

		// Absolute world coordinates for 1st person controller movement, not optimal
		// but it works (Unused)
		[[nodiscard]] std::pair<glm::vec3, glm::vec3> get_height_and_normal(float x, float z);

		float world_scale = 4.0f;
		std::unique_ptr<triangle_list> tri_list;
		size_t size;

	protected:
		std::vector<float> height_map;
		shader_manager& sm;
	};
}