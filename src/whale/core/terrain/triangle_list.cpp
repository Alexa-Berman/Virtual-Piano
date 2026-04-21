#include "triangle_list.h"

#include "basic_terrain.h"

#include <glm/glm.hpp>

namespace whale
{
	triangle_list::triangle_list(int width, int depth, basic_terrain& t)
		: width(width), depth(depth)
	{
		glCreateVertexArrays(1, &vao);
		glCreateBuffers(1, &vbo);
		glCreateBuffers(1, &normal_vbo);
		glCreateBuffers(1, &ibo);

		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(vertex));
		glVertexArrayAttribBinding(vao, 0, 0);

		glEnableVertexArrayAttrib(vao, 1);
		glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(vao, 1, normal_vbo, 0, 3 * sizeof(float));
		glVertexArrayAttribBinding(vao, 1, 1);

		glVertexArrayElementBuffer(vao, ibo);


		vertices.resize(width * depth);


		size_t index = 0;

		for (int z = 0; z < depth; z++)
		{
			for (int x = 0; x < width; x++)
			{
				vertices.at(index) = vertex(t, x, z);
				index++;
			}
		}

		int num_quads = (width - 1) * (depth - 1);
		indices.resize(num_quads * 6);

		index = 0;
		for (int z = 0; z < depth - 1; z++)
		{
			for (int x = 0; x < width - 1; x++)
			{
				auto idx_bottom_left = z * width + x;
				auto idx_top_left = (z + 1) * width + x;
				auto idx_top_right = (z + 1) * width + x + 1;
				auto idx_bottom_right = z * width + x + 1;

				// Top left triangle
				indices[index++] = idx_bottom_left;
				indices[index++] = idx_top_left;
				indices[index++] = idx_top_right;

				// Bottom left triangle
				indices[index++] = idx_bottom_left;
				indices[index++] = idx_top_right;
				indices[index++] = idx_bottom_right;
			}
		}

		normals.resize(width * depth);

		for (auto i = 0uz; i < indices.size(); i += 3)
		{
			auto i0 = indices.at(i);
			auto i1 = indices.at(i + 1);
			auto i2 = indices.at(i + 2);
			auto v1 = vertices.at(i1).pos - vertices.at(i0).pos;
			auto v2 = vertices.at(i2).pos - vertices.at(i0).pos;
			auto normal = glm::normalize(glm::cross(v1, v2));
			normals.at(i0) += normal;
			normals.at(i1) += normal;
			normals.at(i2) += normal;
		}

		for (auto& n : normals)
		{
			n = glm::normalize(n);
		}

		auto center_at_origin = glm::translate(glm::mat4(1.0f), glm::vec3(float(-width * 2.0f), 0.0f, float(-depth * 2.0)));
		for (auto& v : vertices)
		{
			v.pos = center_at_origin * glm::vec4(v.pos, 1.0f);
		}

		glNamedBufferData(vbo, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glNamedBufferData(normal_vbo, sizeof(normals[0]) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glNamedBufferData(ibo, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	triangle_list::~triangle_list()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &normal_vbo);
		glDeleteBuffers(1, &ibo);
	}

	void triangle_list::render()
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, (depth - 1) * (width - 1) * 6, GL_UNSIGNED_INT, nullptr);
	}

	triangle_list::vertex::vertex(basic_terrain& t, int x, int z)
	{
		float y = t.get_height(x, z);
		pos = glm::vec3(x * t.world_scale, y, z * t.world_scale);
	}
}
