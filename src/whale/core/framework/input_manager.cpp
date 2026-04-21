#include "input_manager.h"

#include <GLFW/glfw3.h>

namespace whale
{
	void input_manager::event(const app_event& e)
	{
		std::visit(overload{
			[&](const key_event& k)
			{
				if (key_map.contains(k.key))
				{
					for (auto& hotkey : key_map.at(k.key))
					{
						switch (k.action)
						{
							case GLFW_PRESS:
							{
								if (hotkey.type == hotkey_type::key_down)
								{
									hotkey.func(k.modifiers, 1.0f);
								}
								hotkey.state = true;
								hotkey.modifiers = k.modifiers;
								break;
							}
							case GLFW_RELEASE:
							{
								if (hotkey.type == hotkey_type::key_up)
								{
									hotkey.func(k.modifiers, 1.0f);
								}
								hotkey.state = false;
								hotkey.modifiers = k.modifiers;
								break;
							}
						}
					}
				}
			},
			[&](auto&) {}
			}, e.data);
	}

	void input_manager::update(float dt)
	{
		for (const auto& [key, hotkeys] : key_map)
		{
			for (const auto& hotkey : hotkeys)
			{
				if (hotkey.type == hotkey_type::key_held && hotkey.state == true)
				{
					hotkey.func(hotkey.modifiers, dt);
				}
				else if (hotkey.type == hotkey_type::key_released && hotkey.state == false)
				{
					hotkey.func(hotkey.modifiers, dt);
				}
			}
		}
	}

	hotkey& input_manager::register_hotkey(int key, hotkey_type type, const hotkey_func& func)
	{
		// Note that I'm explicitly allowing the "construct if not found" behavior because
		// we want to support adding new keybinds that might have the same key associated with them
		return key_map[key].emplace_back(key, type, func);
	}

	void input_manager::remove_hotkey(int key, hotkey_type type)
	{
		if (key_map.contains(key))
		{
			auto& hotkeys = key_map.at(key);
			std::erase_if(hotkeys, [type](const hotkey& hk)
			{
				return hk.type == type;
			});
		}
	}

	void input_manager::remove_hotkey(const hotkey& hk)
	{
		remove_hotkey(hk.key, hk.type);
	}
}