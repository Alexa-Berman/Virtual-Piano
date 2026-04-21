#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace whale
{
	class basic_camera
	{
	public:
		basic_camera() = default;
		basic_camera(const glm::quat& orientation, const glm::vec3& position, const glm::mat4 projection)
			: orientation(orientation), position(position), projection(projection) {}
		virtual ~basic_camera() = default;

		virtual glm::mat4 view_matrix() const final;
		virtual glm::mat4 projection_matrix() const final { return projection; }
		virtual glm::quat get_orientation() const final { return orientation; }
		virtual glm::vec3 get_position() const final { return position; }

		virtual glm::vec3 forward() const final;
		virtual glm::vec3 back() const final;
		virtual glm::vec3 left() const final;
		virtual glm::vec3 right() const final;
		virtual glm::vec3 up() const final;
		virtual glm::vec3 down() const final;

	protected:
		glm::quat orientation;
		glm::vec3 position;
		glm::mat4 projection;
	};
}