#include "controllable_camera.h"

#include "app_event.h"

namespace whale
{
	class freecam_controller : public controllable_camera
	{
	public:
		freecam_controller() = default;
		freecam_controller(const glm::quat& orientation, const glm::vec3& position,
						   const glm::mat4& projection, whale::input_manager& im)
			: controllable_camera(orientation, position, projection, im) {}

		virtual ~freecam_controller() = default;

		void update(const mouse_move& m);

	private:
	};
}