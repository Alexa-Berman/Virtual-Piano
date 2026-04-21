#include "application.h"

#include <iostream>

namespace whale
{
	// https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions
	void debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, GLchar const* message, void const*)
	{
		auto const src_str = [source]() {
			switch (source)
			{
			case GL_DEBUG_SOURCE_API: return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER: return "OTHER";
			default: return "UNKNOWN";
			}
		}();

		auto const type_str = [type]() {
			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR: return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER: return "MARKER";
			case GL_DEBUG_TYPE_OTHER: return "OTHER";
			default: return "UNKNOWN";
			}
		}();

		auto const severity_str = [severity]() {
			switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW: return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
			default: return "UNKNOWN";
			}
		}();
		std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
	}

	application::application(const creation_flags& flags)
		: active_layer(std::make_shared<empty_layer>(*this))
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
		#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* video_mode = glfwGetVideoMode(monitor);
		window_width = video_mode->width;
		window_height = video_mode->height;
		switch (flags.window_mode)
		{
		case window_mode::windowed:
		{
			window_width = static_cast<int>(flags.resolution_x),
			window_height = static_cast<int>(flags.resolution_y),
			window = glfwCreateWindow(static_cast<int>(flags.resolution_x), static_cast<int>(flags.resolution_y), flags.window_title.c_str(), nullptr, nullptr);
			break;
		}
		case window_mode::borderless:
		{
			glfwWindowHint(GLFW_RED_BITS, video_mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, video_mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, video_mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, video_mode->refreshRate);
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
			 
			window = glfwCreateWindow(video_mode->width, video_mode->height, flags.window_title.c_str(), nullptr, nullptr);
			break;
		}
		case window_mode::fullscreen:
		{
			window = glfwCreateWindow(video_mode->width, video_mode->height, flags.window_title.c_str(), monitor, nullptr);
			break;
		}
		}

		glfwSetWindowUserPointer(window, this);
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSwapInterval(flags.vsync);

		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

#if defined(NDEBUG) || defined(__MACOS__)
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(debug_message_callback, nullptr);
#endif

		glfwSetFramebufferSizeCallback(window, []([[maybe_unused]] GLFWwindow* window, int width, int height)
		{
			auto self = static_cast<application*>(glfwGetWindowUserPointer(window));
			self->window_width = width;
			self->window_height = height;
			glViewport(0, 0, width, height);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
		{
			auto self = static_cast<application*>(glfwGetWindowUserPointer(window));

			app_event e(key_event{ key, action, mods });

			self->push_event(e);
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto self = static_cast<application*>(glfwGetWindowUserPointer(window));

			app_event e(mouse_button{ button, action, mods });

			self->push_event(e);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{
			auto self = static_cast<application*>(glfwGetWindowUserPointer(window));

			app_event e(mouse_move{ static_cast<float>(xpos), static_cast<float>(ypos) });
			
			self->push_event(e);
		});
	}

	application::~application()
	{
		glfwTerminate();
	}

	void application::run()
	{
		float t0 = 0.0f;
		float dt = 1.0f / 60.0f;
		while (!glfwWindowShouldClose(window))
		{
			float t1 = static_cast<float>(glfwGetTime());
			dt = t1 - t0;
			t0 = static_cast<float>(glfwGetTime());

			glfwPollEvents();
			dispatch_events();

			active_layer->update(dt);
			active_layer->render();

			glfwSwapBuffers(window);
		}
	}
}
