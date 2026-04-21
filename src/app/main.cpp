#include "application.h"
#include "exception.h"
#include "main_viewport.h"
#include "miniaudio.h"
#include <memory>
#include <print>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	whale::application::creation_flags cf;
	cf.window_mode = whale::application::window_mode::windowed;
	cf.resolution_x = 800;
	cf.resolution_y = 600;
	cf.window_title = "M4OEP";

	try
	{
		whale::application app(cf);
		app.bind_layer(std::make_shared<M4OEP::main_viewport>(app));

		app.run();
	}
	catch (const whale::exception & e)
	{
		// std::println("{}", e.what());
	}

	return 0;
}
