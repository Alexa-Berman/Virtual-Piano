target_include_directories(whale PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(whale PRIVATE
	uv_sphere.cpp
)
