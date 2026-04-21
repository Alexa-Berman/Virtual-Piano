#include "app_event.h"
#include "shader_manager.h"
#include "shader_program_opengl.h"
#include "miniaudio.h"

namespace M4OEP
{
	using namespace whale;

	class keyboard
	{
	public:
		enum class voice_type
		{
			piano,
			synth
		};

		keyboard(shader_manager& sm);
		void event(const app_event& event);
		void update(float dt);
		void render();

		void set_voice_type(voice_type type);

		float white_key_fades[7]{};
		float black_key_fades[5]{};

	private:
		float fade_out_speed = 0.6f;
		GLuint key_vertex_array;
		GLuint key_vertex_buffer;

		shader_program keys_program;

		voice_type voice = voice_type::piano;

		enum class render_pass
		{
			outline,
			base_color
		};

		enum class key_type
		{
			white,
			black
		};

	};
}