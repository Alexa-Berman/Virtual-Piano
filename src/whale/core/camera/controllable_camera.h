#pragma once

#include "basic_camera.h"

#include "input_manager.h"

namespace whale
{
	class controllable_camera : public basic_camera
	{
	public:
		controllable_camera() = default;
		controllable_camera(const glm::quat& orientation, const glm::vec3& position,
							const glm::mat4& projection, whale::input_manager& im);
		virtual ~controllable_camera() = default;

	void move(const glm::vec3& v, float dt) { position += v * speed * dt; }
	virtual float get_speed() const { return speed; }
	virtual void set_speed(float new_speed) { speed = new_speed; }

	protected:
		float speed = 1.0f;
		input_manager* input_manager;
	};
}