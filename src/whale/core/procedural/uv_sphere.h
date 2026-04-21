#pragma once

#include "mesh.h"

#include "basic_camera.h"
#include "shader_manager.h"
#include "shader_program_opengl.h"

#include <glad/glad.h>

namespace whale
{
	class uv_sphere : public mesh
	{
	public:
		uv_sphere(uint32_t resolution);

		void render(shader_program& program, basic_camera& cam, int instance_count) override;

	private:
		shader_manager sm;
		[[maybe_unused]] size_t resolution;

		uint32_t triangle_count;
		GLuint vao;
		GLuint vbo;
		GLuint ibo;
	};
}