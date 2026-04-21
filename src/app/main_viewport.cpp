#include "main_viewport.h"

#include "application.h"
#include "uniform_bindings.h"

#include <iostream>
#include <exception>
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
using namespace std;


#include <stdio.h>

#include <cmath>

namespace M4OEP
{
	using glm::vec3;
	using glm::vec4;
	
	static ma_engine engine; 

	ma_device audio_device;
	ma_device_config device_config;
	ma_waveform sin_wave;
	ma_waveform_config wave_config;

	int octave = 4;
	bool synth = false;

	void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
	{
		ma_waveform* p_wave;
		p_wave = reinterpret_cast<ma_waveform*>(pDevice->pUserData);
		ma_waveform_read_pcm_frames(p_wave, pOutput, frameCount, NULL);
	}

	void play_synth(bool active, ma_sound* sound,
					ma_waveform* waveform, float frequency){
		if (active) {
			ma_sound_stop(sound);
			ma_sound_uninit(sound);
		}
		ma_waveform_config config = ma_waveform_config_init(ma_format_f32, 2, 48000,
						ma_waveform_type_sawtooth, 0.2, frequency * pow(2, octave - 1));
		ma_waveform_init(&config, waveform);
		ma_sound_init_from_data_source(&engine, waveform, 0, NULL, sound);
		ma_sound_start(sound);
	}

	void play_piano(string note, int octave){
		string file = string(PROJECT_ROOT) + "/Notes/" + note + std::to_string(octave) + ".wav";
		ma_engine_play_sound(&engine, file.c_str(), NULL);
	}
	
	// white key synth stuff

	static ma_waveform c_waveform;
	static ma_sound c_sound;
	static bool c_active = false;

	static ma_waveform d_waveform;
	static ma_sound d_sound;
	static bool d_active = false;

	static ma_waveform e_waveform;
	static ma_sound e_sound;
	static bool e_active = false;

	static ma_waveform f_waveform;
	static ma_sound f_sound;
	static bool f_active = false;

	static ma_waveform g_waveform;
	static ma_sound g_sound;
	static bool g_active = false;

	static ma_waveform a_waveform;
	static ma_sound a_sound;
	static bool a_active = false;

	static ma_waveform b_waveform;
	static ma_sound b_sound;
	static bool b_active = false;

	static ma_waveform c_up_waveform;
	static ma_sound c_up_sound;
	static bool c_up_active = false;

	// black key synth stuff

	static ma_waveform c_sharp_waveform;
	static ma_sound c_sharp_sound;
	static bool c_sharp_active = false;

	static ma_waveform d_sharp_waveform;
	static ma_sound d_sharp_sound;
	static bool d_sharp_active = false;

	static ma_waveform f_sharp_waveform;
	static ma_sound f_sharp_sound;
	static bool f_sharp_active = false;

	static ma_waveform g_sharp_waveform;
	static ma_sound g_sharp_sound;
	static bool g_sharp_active = false;

	static ma_waveform a_sharp_waveform;
	static ma_sound a_sharp_sound;
	static bool a_sharp_active = false;

	void main_viewport::start()
	{
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
			printf("Failed to initialize audio engine\n");
			return;
		}

		device_config = ma_device_config_init(ma_device_type_playback);
		device_config.playback.format = ma_format_f32;
		device_config.playback.channels = 2;
		device_config.sampleRate = 48000;
		device_config.dataCallback = data_callback;
		device_config.pUserData = &sin_wave;

		if (ma_device_init(NULL, &device_config, &audio_device) != MA_SUCCESS)
			throw std::runtime_error("Failed to open audio device");

		if (ma_device_start(&audio_device) != MA_SUCCESS)
			throw std::runtime_error("Failed to start audio device");


		input_manager.register_hotkey(GLFW_KEY_ESCAPE, hotkey_type::key_down, [](int, float)
		{
			glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
		});

		// audio stuff

		// up arrow raises octave
		input_manager.register_hotkey(GLFW_KEY_UP, hotkey_type::key_down, [](int, float){
			if(octave < 7){
				octave++;
			}
		});

		// down arrow lowers octave
		input_manager.register_hotkey(GLFW_KEY_DOWN, hotkey_type::key_down, [](int, float){
			if(octave > 1){
				octave--;
			}
		});

		// octave 1
		input_manager.register_hotkey(GLFW_KEY_1, hotkey_type::key_down, [](int, float){
			octave = 1;
		});

		// octave 2
		input_manager.register_hotkey(GLFW_KEY_2, hotkey_type::key_down, [](int, float){
			octave = 2;
		});

		// octave 3
		input_manager.register_hotkey(GLFW_KEY_3, hotkey_type::key_down, [](int, float){
			octave = 3;
		});

		// octave 4
		input_manager.register_hotkey(GLFW_KEY_4, hotkey_type::key_down, [](int, float){
			octave = 4;
		});

		// octave 5
		input_manager.register_hotkey(GLFW_KEY_5, hotkey_type::key_down, [](int, float){
			octave = 5;
		});

		// octave 6
		input_manager.register_hotkey(GLFW_KEY_6, hotkey_type::key_down, [](int, float){
			octave = 6;
		});
		
		// octave 7
		input_manager.register_hotkey(GLFW_KEY_7, hotkey_type::key_down, [](int, float){
			octave = 7;
		});

		// toggle synth mode
		input_manager.register_hotkey(GLFW_KEY_0, hotkey_type::key_down, [](int, float){
			synth = !synth;
		});
		
		// mystery key
		input_manager.register_hotkey(GLFW_KEY_R, hotkey_type::key_down, [](int, float){
			ma_engine_play_sound(&engine, PROJECT_ROOT "/sound.wav", NULL);
		});

		// White keys

		// c
		input_manager.register_hotkey(GLFW_KEY_A, hotkey_type::key_down, [&](int, float){
			keyboard.white_key_fades[0] = 1.0f;

			if (synth) {
				play_synth(c_active, &c_sound, &c_waveform, 16.35);
				c_active = true;
			} else {
				play_piano("c", octave);
			}
		});

		// d
		input_manager.register_hotkey(GLFW_KEY_S, hotkey_type::key_down, [&](int, float){
			keyboard.white_key_fades[1] = 1.0f;

			if (synth) {
				play_synth(d_active, &d_sound, &d_waveform, 18.35);
				d_active = true;
			} else {
				play_piano("d", octave);
			}
		});

		// e
		input_manager.register_hotkey(GLFW_KEY_D, hotkey_type::key_down, [&](int, float) {
			keyboard.white_key_fades[2] = 1.0f;

			if (synth){
				play_synth(e_active, &e_sound, &e_waveform, 20.6);
				e_active = true;
			} else {
				play_piano("e", octave);
			}
		});
		// f
		input_manager.register_hotkey(GLFW_KEY_F, hotkey_type::key_down, [&](int, float){
			keyboard.white_key_fades[3] = 1.0f;

			if (synth){
				play_synth(f_active, &f_sound, &f_waveform, 21.83);
				f_active = true;
			} else{
				play_piano("f", octave);
			}
		});
		// g
		input_manager.register_hotkey(GLFW_KEY_G, hotkey_type::key_down, [&](int, float){
			keyboard.white_key_fades[4] = 1.0f;

			if (synth){
				play_synth(g_active, &g_sound, &g_waveform, 24.5);
				g_active = true;
			} else{
				play_piano("g", octave);
			}
		});
		// a 
		input_manager.register_hotkey(GLFW_KEY_H, hotkey_type::key_down, [&](int, float){
			keyboard.white_key_fades[5] = 1.0f;

			if (synth){
				play_synth(a_active, &a_sound, &a_waveform, 27.5);
				a_active = true;
			} else{
				play_piano("a", octave);
			}
		});
		// b 
		input_manager.register_hotkey(GLFW_KEY_J, hotkey_type::key_down, [&](int, float){
			keyboard.white_key_fades[6] = 1.0f;

			if (synth){
				play_synth(b_active, &b_sound, &b_waveform, 30.87);
				b_active = true;
			} else{
				play_piano("b", octave);
			}
		});
		// c up the octave
		input_manager.register_hotkey(GLFW_KEY_K, hotkey_type::key_down, [](int, float){

			if (synth){
				play_synth(c_up_active, &c_up_sound, &c_up_waveform, 32.7);
				c_up_active = true;
			} else{
				play_piano("c", octave+1);
			}
		});


		// black keys
		// c#
		input_manager.register_hotkey(GLFW_KEY_W, hotkey_type::key_down, [&](int, float){
			keyboard.black_key_fades[0] = 1.0f;

			if (synth){
				play_synth(c_sharp_active, &c_sharp_sound, &c_sharp_waveform, 17.32);
				c_sharp_active = true;
			} else{
				play_piano("c-", octave);
			}
		});
		// d#
		input_manager.register_hotkey(GLFW_KEY_E, hotkey_type::key_down, [&](int, float){
			keyboard.black_key_fades[1] = 1.0f;

			if (synth){
				play_synth(d_sharp_active, &d_sharp_sound, &d_sharp_waveform, 19.45);
				d_sharp_active = true;
			} else{
				play_piano("d-", octave);
			}
		});
		// f#
		input_manager.register_hotkey(GLFW_KEY_T, hotkey_type::key_down, [&](int, float){
			keyboard.black_key_fades[2] = 1.0f;

			if (synth){
				play_synth(f_sharp_active, &f_sharp_sound, &f_sharp_waveform, 23.12);
				f_sharp_active = true;
			} else{
				play_piano("f-", octave);
			}
		});
		// g#
		input_manager.register_hotkey(GLFW_KEY_Y, hotkey_type::key_down, [&](int, float){
			keyboard.black_key_fades[3] = 1.0f;

			if (synth){
				play_synth(g_sharp_active, &g_sharp_sound, &g_sharp_waveform, 25.96);
				g_sharp_active = true;
			} else{
				play_piano("g-", octave);
			}
		});
		// a# 
		input_manager.register_hotkey(GLFW_KEY_U, hotkey_type::key_down, [&](int, float){
			keyboard.black_key_fades[4] = 1.0f;

			if (synth){
				play_synth(a_sharp_active, &a_sharp_sound, &a_sharp_waveform, 29.14);
				a_sharp_active = true;
			} else{
				play_piano("a-", octave);
			}
		});

		input_manager.register_hotkey(GLFW_KEY_A, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&c_sound);
			ma_sound_uninit(&c_sound);
			c_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_S, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&d_sound);
			ma_sound_uninit(&d_sound);
			d_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_D, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&e_sound);
			ma_sound_uninit(&e_sound);
			e_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_F, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&f_sound);
			ma_sound_uninit(&f_sound);
			f_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_G, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&g_sound);
			ma_sound_uninit(&g_sound);
			g_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_H, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&a_sound);
			ma_sound_uninit(&a_sound);
			a_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_J, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&b_sound);
			ma_sound_uninit(&b_sound);
			b_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_K, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&c_up_sound);
			ma_sound_uninit(&c_up_sound);
			c_up_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_W, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&c_sharp_sound);
			ma_sound_uninit(&c_sharp_sound);
			c_sharp_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_E, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&d_sharp_sound);
			ma_sound_uninit(&d_sharp_sound);
			d_sharp_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_T, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&f_sharp_sound);
			ma_sound_uninit(&f_sharp_sound);
			f_sharp_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_Y, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&g_sharp_sound);
			ma_sound_uninit(&g_sharp_sound);
			g_sharp_active = false;
		});

		input_manager.register_hotkey(GLFW_KEY_U, hotkey_type::key_up, [&](int, float){
			ma_sound_stop(&a_sharp_sound);
			ma_sound_uninit(&a_sharp_sound);
			a_sharp_active = false;
		});

	}
	void main_viewport::end()
	{
		ma_engine_uninit(&engine);
	}

	void main_viewport::event([[maybe_unused]] const app_event& event)
	{
		input_manager.event(event);
		keyboard.event(event);
	}

	void main_viewport::update([[maybe_unused]] float dt)
	{
		input_manager.update(dt);
		keyboard.update(dt);
	}

	void main_viewport::render()
	{
		using namespace glm;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		keyboard.render();

	}
}