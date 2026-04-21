#include "texture_manager.h"

namespace whale
{
	texture_data texture_manager::load(const std::filesystem::path& path)
	{
		int w, h, c;
		stbi_set_flip_vertically_on_load(true);
		uint8_t* data = stbi_load(path.string().c_str(), &w, &h, &c, 0);
		return texture_data(w, h, c, data);
	}
}