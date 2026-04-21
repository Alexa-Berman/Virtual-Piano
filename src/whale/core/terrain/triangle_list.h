#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace whale
{
	class basic_terrain;

	class triangle_list
	{
	public:
		struct vertex
		{
			glm::vec3 pos;
			vertex() = default;
			vertex(basic_terrain& t, int x, int z);
		};

		std::vector<vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<glm::vec3> normals;

		triangle_list(int width, int depth, basic_terrain& t);
		~triangle_list();

		void render();

	private:

		int width;
		int depth;
		GLuint vao;
		GLuint vbo;
		GLuint normal_vbo;
		GLuint ibo;
	};

}