target_include_directories(whale PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(whale PRIVATE
	application_opengl.cpp
	basic_shader_opengl.cpp
	compute_shader_opengl.cpp
	fragment_shader_opengl.cpp
	shader_program_opengl.cpp
	vertex_shader_opengl.cpp
)