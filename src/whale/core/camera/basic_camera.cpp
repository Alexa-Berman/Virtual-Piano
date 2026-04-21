#include "basic_camera.h"

namespace whale
{
	glm::mat4 basic_camera::view_matrix() const
	{
		return glm::mat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -position);
	}

	glm::vec3 basic_camera::forward() const
	{
		auto forward = orientation * glm::vec3(0, 0, -1);
		forward.y = 0;
		return glm::normalize(forward);
	}

	glm::vec3 basic_camera::back() const
	{
		return -(forward());
	}

	glm::vec3 basic_camera::left() const
	{
		return orientation * glm::vec3(-1, 0, 0);
	}

	glm::vec3 basic_camera::right() const
	{
		return -(left());
	}

	glm::vec3 basic_camera::up() const
	{
		return glm::vec3(0, 1, 0);
	}
	
	glm::vec3 basic_camera::down() const
	{
		return glm::vec3(0, -1, 0);
	}
}