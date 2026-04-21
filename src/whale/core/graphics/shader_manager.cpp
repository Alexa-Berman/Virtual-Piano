#include "shader_manager.h"

#include "exception.h"
#include "compute_shader.h"
#include "fragment_shader.h"
#include "vertex_shader.h"

#include <fstream>

namespace whale
{
	shader_manager::~shader_manager()
	{
		for (const auto& [location, ubo] : uniform_buffers)
		{
			glDeleteBuffers(1, &ubo);
		}

		for (const auto& [location, ssbo] : storage_buffers)
		{
			glDeleteBuffers(1, &ssbo);
		}
	}

	std::unique_ptr<basic_shader> shader_manager::load(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			throw exception("File does not exist");

		std::string processed_source = resolve_includes(path);
		if (auto ext = path.extension(); ext == ".vert")
		{
			return std::make_unique<vertex_shader>(processed_source);
		}
		else if (ext == ".frag")
		{
			return std::make_unique<fragment_shader>(processed_source);
		}
		else if (ext == ".comp")
		{
			return std::make_unique<compute_shader>(processed_source);
		}
		else
		{
			throw exception("Invalid shader format");
		}
	}

	std::string shader_manager::resolve_includes(const std::filesystem::path& current_file)
	{	
		std::ifstream source(current_file);
		std::string processed_source;
		std::string line;
		size_t line_number = 1;
		while (std::getline(source, line))
		{
			if (line.starts_with("#include"))
			{
				size_t begin = line.find('"');
				if (begin != std::string::npos)
				{
					if (size_t end = line.find('"', begin + 1); end != std::string::npos)
					{
						std::string file_to_include = line.substr(begin + 1, end - begin - 1);
						std::filesystem::path include_path = current_file.parent_path() / file_to_include;

						processed_source += resolve_includes(include_path);
						processed_source += '\n';
					}
					else if (begin != std::string::npos && end == std::string::npos)
					{
						throw exception("Shader preprocessor error " + current_file.string() + " - line " + std::to_string(line_number) + " missing delimiter \"");					}
					else
					{
						throw exception("Shader preprocessor error " + current_file.string() + " - line " + std::to_string(line_number) + " syntax error - did you mean #include \"shader.glsl\"?");
					}
				}
			}
			else
			{
				processed_source += line + '\n';
			}
			line_number++;
		}
		return processed_source;
	}

}