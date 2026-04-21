#pragma once

#include "basic_layer.h"

#ifdef PLATFORM_OPENGL
#include <glad/glad.h>	
#include <GLFW/glfw3.h>
#endif

#include <cstdint>
#include <memory>
#include <queue>
#include <string>

namespace whale
{
	class application
	{
	public:
		enum class window_mode
		{
			windowed,
			borderless,
			fullscreen
		};

		struct creation_flags
		{
			size_t resolution_x = 800;
			size_t resolution_y = 600;
			window_mode window_mode = window_mode::windowed;
			std::string window_title = "Untitled";
			bool vsync = true;
		};

		int window_width;
		int window_height;

		explicit application(const creation_flags& flags);
		~application();

		void bind_layer(std::shared_ptr<basic_layer> layer);
		void run();

	private:
		std::shared_ptr<basic_layer> active_layer;

	#ifdef PLATFORM_OPENGL
		using native_handle = GLFWwindow*;
	#endif
		native_handle window;

		std::queue<app_event> event_queue;
		void push_event(const app_event& event);
		void dispatch_events();
	};
}