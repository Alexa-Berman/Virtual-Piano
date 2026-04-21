#pragma once

#include "app_event.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace whale
{
	enum class hotkey_type
	{
		key_down,
		key_up,
		key_held,
		key_released
	};

	struct hotkey
	{
		int key;
		hotkey_type type;
		std::function<void(int modifiers, float dt)> func;
		bool state;
		int modifiers;
	};

	class input_manager
	{
	public:
		using hotkey_func = std::function<void(int modifiers, float dt)>;

		void event(const app_event& e);
		void update(float dt);

		hotkey& register_hotkey(int key, hotkey_type type, const hotkey_func& func);
		void remove_hotkey(int key, hotkey_type type);
		void remove_hotkey(const hotkey& hk);

	private:

		std::unordered_map<int, std::vector<hotkey>> key_map;
	};
}