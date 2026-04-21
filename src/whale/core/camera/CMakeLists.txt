target_include_directories(whale PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(whale PRIVATE
	basic_camera.cpp
	controllable_camera.cpp
	freecam_controller.cpp
)
