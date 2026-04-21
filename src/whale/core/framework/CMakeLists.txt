target_include_directories(whale PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(whale PRIVATE
	application.cpp
	input_manager.cpp
)
