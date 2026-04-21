#include "uv_sphere.h"

#include "shader_program_opengl.h"
#include <iostream>
#include <glad/glad.h>

namespace whale
{
	uv_sphere::uv_sphere(uint32_t resolution)
		: resolution(resolution), triangle_count(resolution * resolution * 6)
	{
		auto compute_program = shader_program(sm.load("shaders/meshify_sphere.comp"));

		// Resolution + 1 for vertices to account for the wrap-around seam
		uint32_t vertex_count = (resolution + 1) * (resolution + 1);
		// Resolution squared for the number of quads, 6 indices per quad
		uint32_t index_count = (resolution * resolution) * 6;

		vbo = sm.set_storage_buffer(0, vertex_count * sizeof(glm::vec4) * 2);
		ibo = sm.set_storage_buffer(1, index_count * sizeof(uint32_t));

		compute_program.set_uniform(0, resolution);

		compute_program.use();
		uint32_t num_groups = (resolution + 1 + 15) / 16; // +1 for the last vertex
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ibo);
		glDispatchCompute(num_groups, num_groups, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);

		glCreateVertexArrays(1, &vao);
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(glm::vec4) * 2);
		glVertexArrayElementBuffer(vao, ibo);

		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);

		glEnableVertexArrayAttrib(vao, 1);
		glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4));
		glVertexArrayAttribBinding(vao, 1, 0);
	}

	void uv_sphere::render(shader_program& program, basic_camera&, int instance_count)
	{
		program.use();
		glBindVertexArray(vao);
		glDrawElementsInstanced(GL_TRIANGLES, triangle_count, GL_UNSIGNED_INT, nullptr, instance_count);
	}
}