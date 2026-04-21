#include "basic_layer.h"

#include "freecam_controller.h"
#include "input_manager.h"
#include "keyboard.h"
#include "shader_manager.h"
#include "shader_program_opengl.h"
#include "texture_manager.h"

#include <glad/glad.h>	
#include <glm/glm.hpp>
#include "miniaudio.h"
#include <memory>

namespace M4OEP
{
	using namespace whale;

	class main_viewport : public basic_layer
	{
	public:
		main_viewport(application& app) : basic_layer(app) {}
		virtual ~main_viewport() = default;

		virtual void start() override;
		virtual void end() override;
		virtual void event(const app_event& event) override;
		virtual void update(float dt) override;
		virtual void render() override;

	private:
		input_manager input_manager;
		shader_manager shader_manager;
		[[maybe_unused]] texture_manager texture_manager;

		keyboard keyboard{shader_manager};
	};
}