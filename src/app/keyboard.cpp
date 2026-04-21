#include "keyboard.h"
#include "miniaudio.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace M4OEP
{
	keyboard::keyboard(shader_manager& sm) // gotta find a better way to manage the asset paths but this is fine for now
		: keys_program(sm.load(PROJECT_ROOT "/shaders/key.vert"), sm.load(PROJECT_ROOT "/shaders/key.frag"))
	{
		glGenVertexArrays(1, &key_vertex_array);
		glGenBuffers(1, &key_vertex_buffer);

		glBindVertexArray(key_vertex_array);

		glBindBuffer(GL_ARRAY_BUFFER, key_vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// unit quad with 1 in Z for translations and UVs for texture/shading maybe
		float quad_data[] = {
		    -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
		     0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
		    -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,

		    -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,
		     0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
		     0.5f,  0.5f,  1.0f,  1.0f,  1.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, key_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

		for (int i = 0; i < 7; i++)
		{
			white_key_fades[i] = 0.0f;
		}
		for (int i = 0; i < 5; i++)
		{
			black_key_fades[i] = 0.0f;
		}

	}

	// TODO: implement this
	void keyboard::event(const app_event& event)
	{
		std::visit(overload{
			[&]([[maybe_unused]] const mouse_move& m)
			{
				// TODO: mouse move stuff
			},
			[&](const mouse_button& b)
			{
				// button stuff
			},
			[&](const auto&) {}
			}, event.data);
	}
#ifdef max // weird windows macro
#undef max
#endif
	void keyboard::update(float dt)
	{
		for (int i = 0; i < 7; i++)
		{
			white_key_fades[i] = std::max(0.0f, white_key_fades[i] - fade_out_speed * dt);
		}

		for (int i = 0; i < 5; i++) 
		{
			black_key_fades[i] = std::max(0.0f, black_key_fades[i] - fade_out_speed * dt);
		}
	}

	void keyboard::render()
	{
		keys_program.use();
		int pass_loc = glGetUniformLocation(keys_program.handle(), "render_pass");
		int key_loc = glGetUniformLocation(keys_program.handle(), "key_type");
		int white_fades_loc = glGetUniformLocation(keys_program.handle(), "white_key_fades");
		int black_fades_loc = glGetUniformLocation(keys_program.handle(), "black_key_fades");



		keys_program.set_uniform(white_fades_loc, white_key_fades, sizeof(white_key_fades) / sizeof(white_key_fades[0]));
		keys_program.set_uniform(black_fades_loc, black_key_fades, sizeof(black_key_fades) / sizeof(black_key_fades[0]));

		// White key pass
		keys_program.set_uniform(key_loc, static_cast<int>(key_type::white));
		keys_program.set_uniform(pass_loc, static_cast<int>(render_pass::outline));
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 7);
		keys_program.set_uniform(pass_loc, static_cast<int>(render_pass::base_color));
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 7);

		// Black key pass
		keys_program.set_uniform(key_loc, static_cast<int>(key_type::black));
		keys_program.set_uniform(pass_loc, static_cast<int>(render_pass::outline));
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 5);
		keys_program.set_uniform(pass_loc, static_cast<int>(render_pass::base_color));
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 5);
	}

	void keyboard::set_voice_type(voice_type type)
	{
		voice = type;
	}
}