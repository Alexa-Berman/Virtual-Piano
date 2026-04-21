#pragma once

#include "basic_camera.h"

#include <glm/glm.hpp>

namespace whale::uniform_bindings
{
	using glm::mat4;
	using glm::vec3;
	using glm::vec4;

	struct transform
	{
		mat4 model;
		mat4 view;
		mat4 projection;
		mat4 mvp;
		mat4 vp;

		transform(const basic_camera& cam) { set(cam, mat4(1.0f)); }

		void set(const basic_camera& cam, const mat4& new_model)
		{
			this->model = new_model;
			view = cam.view_matrix();
			projection = cam.projection_matrix();
			mvp = projection * view * model;
			vp = projection * view;
		}
	};

	struct material
	{
		float ambient;
		float diffuse;
		float specular;
		float shininess;
	};

	struct light
	{
		vec4 color;
		vec4 pos;
	};
}
