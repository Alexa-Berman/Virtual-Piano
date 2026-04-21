#pragma once

#include <stdexcept>
#include <string>

namespace whale
{
	class exception : public std::runtime_error
	{
	public:
		exception(const char* message) : std::runtime_error(message) {}
		exception(const std::string& message) : std::runtime_error(message) {}
	};
}
