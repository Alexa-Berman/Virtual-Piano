#include "freecam_controller.h"

namespace whale
{
	void freecam_controller::update(const mouse_move& m)
	{
		static float last_x = 0, last_y = 0;
		static bool first_input = true;
		if (first_input) // prevents the camera from snapping at first
		{
			last_x = m.x;
			last_y = m.y;
			first_input = false;
		}
		float xoffset = last_x - m.x;
		float yoffset = last_y - m.y;
		last_x = m.x;
		last_y = m.y;

		// Magic value from quake/source engine games to 
		// emulate the feel of the mouse sensitivity.
		// Determines angle in degrees per "count" of mouse movement
		// so per pixel in the x/y offset here.
		constexpr float m_yaw = 0.022f;

		// This is my sensitivity in tf2 and other source games lol
		const float sensitivity = 1.2f;
		float yaw = glm::radians(xoffset * sensitivity * m_yaw);
		float pitch = glm::radians(yoffset * sensitivity * m_yaw);
		glm::vec3 up(0, 1, 0);
		glm::vec3 right = orientation * glm::vec3(1, 0, 0);

		glm::quat d_yaw = glm::angleAxis(yaw, up);
		glm::quat d_pitch = glm::angleAxis(pitch, right);

		orientation = d_yaw * orientation;
		
		auto wish_orientation = d_pitch * orientation;
		auto wish_up = wish_orientation * glm::vec3(0, 1, 0);
		if (glm::dot(wish_up, up) > 0)
		{
			orientation = wish_orientation;
			orientation = glm::normalize(orientation);
		}
	}

}
