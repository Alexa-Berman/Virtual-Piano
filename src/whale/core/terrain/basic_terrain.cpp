#include "basic_terrain.h"

#include "exception.h"
#include "uniform_bindings.h"

#include <cmath>
#include <fstream>
#include <algorithm>

namespace whale
{
	basic_terrain::basic_terrain(shader_manager& sm)
		:sm(sm) 
	{

	}

	void basic_terrain::load_file(const std::filesystem::path& path)
	{
		std::ifstream file(path, std::ios::binary);
		file.seekg(0, std::ios_base::end);
		auto length = file.tellg();
		file.seekg(0, std::ios_base::beg);

		if (length % sizeof(float) != 0)
		{
			throw exception("Heightmap file has an invalid size");
		}

		size_t float_count = length / sizeof(float);
		size = static_cast<size_t>(std::sqrt(float_count));

		height_map.resize(float_count);
		file.read(reinterpret_cast<char*>(height_map.data()), length);

		tri_list = std::make_unique<triangle_list>((int)size, (int)size, *this);
	}

	void basic_terrain::render(shader_program& program, basic_camera& cam)
	{
		using namespace uniform_bindings;

		transform t(cam);
		t.set(cam, glm::mat4(1.0f));
		sm.set_uniform_buffer(0, t);

		material m;
		m.ambient = 0.1f;
		m.specular = 0.2f;
		m.shininess = 16.0f;
		sm.set_uniform_buffer(1, m);

		program.use();
		tri_list->render();
	}

	float basic_terrain::get_height(int x, int z) const
	{
		return height_map.at(z * size + x);
	}

	// Perform bilinear interpolation on the mesh to calculate position
	// and normal on the mesh in between vertices
	std::pair<glm::vec3, glm::vec3> basic_terrain::get_pos_and_normal(float x, float z)
	{
		auto get_pos = [&](int x, int z){ return tri_list->vertices.at(z * size + x).pos; };
		auto get_norm = [&](int x, int z){ return tri_list->normals.at(z * size + x); };

		x *= (size - 1);
		z *= (size - 1);

		int ix = std::clamp(int(std::floor(x)), 0, static_cast<int>(size - 2));
		int iz = std::clamp(int(std::floor(z)), 0, static_cast<int>(size - 2));

		float factor_x = x - ix;
		float factor_z = z - iz;

		// Positions
		auto x0z0 = get_pos(ix, iz);
		auto x1z0 = get_pos(ix + 1, iz);
		auto x0z1 = get_pos(ix, iz + 1);
		auto x1z1 = get_pos(ix + 1, iz + 1);

		auto interp_top = glm::mix(x0z0, x1z0, factor_x);
		auto interp_bottom = glm::mix(x0z1, x1z1, factor_x);
		auto interp_pos = glm::mix(interp_top, interp_bottom, factor_z);

		// Normals
		x0z0 = get_norm(ix, iz);
		x1z0 = get_norm(ix + 1, iz);
		x0z1 = get_norm(ix, iz + 1);
		x1z1 = get_norm(ix + 1, iz + 1);

		interp_top = glm::mix(x0z0, x1z0, factor_x);
		interp_bottom = glm::mix(x0z1, x1z1, factor_x);
		auto interp_norm = glm::normalize(glm::mix(interp_top, interp_bottom, factor_z));

		return std::make_pair(interp_pos, interp_norm);
	}

	// Unused
	std::pair<glm::vec3,glm::vec3> basic_terrain::get_height_and_normal(float x, float z)
	{
		return std::pair<glm::vec3,glm::vec3>(x, z);
	}
}
