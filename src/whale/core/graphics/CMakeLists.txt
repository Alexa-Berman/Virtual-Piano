target_include_directories(whale PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(whale PRIVATE
	mesh.cpp
	shader_manager.cpp
	stb_impl.cpp
	texture_manager.cpp
)
