#pragma once

#include <variant>

namespace whale
{
	template<class... Ts>
	struct overload : Ts... {
		using Ts::operator()...;
	};

	struct key_event
	{
		int key, action, modifiers;
	};

	struct mouse_button
	{
		int button, action, modifiers;
	};

	struct mouse_move
	{
		float x, y;
	};

	// The reasoning for using value types here is that these event functions
	// will be called very frequently, so avoiding the overhead from virtual
	// functions is desirable
	using event_data = std::variant<key_event, mouse_button, mouse_move>;

	struct app_event
	{
		app_event(const event_data& e) : data(e), handled(false) {}
		event_data data;
		bool handled;
	};
}