#pragma once

#include "app_event.h"

namespace whale
{
	class application; 
	
	class basic_layer
	{
	public:
		friend class application;

		basic_layer(application& app) : app(app) {}
		virtual ~basic_layer() = default;

		virtual void start() = 0;
		virtual void end() = 0;
		virtual void event(const app_event& i) = 0;
		virtual void update(float dt) = 0;
		virtual void render() = 0;

	protected:
		application& app;
	};

	class empty_layer final : public basic_layer
	{
	public:
		empty_layer(application& app) : basic_layer(app) {}
		virtual ~empty_layer() = default;

		virtual void start() {}
		virtual void end() {}
		virtual void event(const app_event&) {}
		virtual void update(float) {}
		virtual void render() {}
	};
}
