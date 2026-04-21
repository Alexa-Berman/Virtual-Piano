#pragma once

#include "basic_camera.h"
#include "shader_program_opengl.h"

#include <glm/glm.hpp>

#include <vector>

namespace whale
{
	class mesh
	{
	public:
		mesh() = default;
		virtual ~mesh() = default;

		virtual void render(shader_program& program, basic_camera& cam, int instance_count) = 0;

	protected:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<uint32_t> indices;
	};
}