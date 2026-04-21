#include "controllable_camera.h"
#include "exception.h"

#include <GLFW/glfw3.h>

namespace whale
{
	controllable_camera::controllable_camera(const glm::quat& orientation, const glm::vec3& position,
											 const glm::mat4& projection, whale::input_manager& im)
		: basic_camera(orientation, position, projection), input_manager(&im)
	{
		input_manager->register_hotkey(GLFW_KEY_W, hotkey_type::key_held, [this](int, float dt)
		{
			move(forward(), dt);
		});

		input_manager->register_hotkey(GLFW_KEY_A, hotkey_type::key_held, [this](int, float dt)
		{
			move(left(), dt);
		});

		input_manager->register_hotkey(GLFW_KEY_S, hotkey_type::key_held, [this](int, float dt)
		{
			move(back(), dt);
		});

		input_manager->register_hotkey(GLFW_KEY_D, hotkey_type::key_held, [this](int, float dt)
		{
			move(right(), dt);
		});

		input_manager->register_hotkey(GLFW_KEY_LEFT_CONTROL, hotkey_type::key_held, [this](int, float dt)
		{
			move(down(), dt);
		});

		input_manager->register_hotkey(GLFW_KEY_SPACE, hotkey_type::key_held, [this](int, float dt)
		{
			move(up(), dt);
		});
	}
}