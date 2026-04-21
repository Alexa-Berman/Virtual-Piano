#include "application.h"

namespace whale
{
	void application::bind_layer(std::shared_ptr<basic_layer> layer)
	{
		active_layer->end();
		active_layer = layer;
		active_layer->app = *this;
		active_layer->start();
	}

	void application::push_event(const app_event& event)
	{
		event_queue.push(event);
	}

	void application::dispatch_events()
	{
		while (!event_queue.empty())
		{
			active_layer->event(event_queue.front());
			event_queue.pop();
		}
	}
}