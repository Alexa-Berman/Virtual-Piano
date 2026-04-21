add_executable(M4OEP)

target_compile_features(M4OEP PRIVATE cxx_std_23)

set_target_properties(M4OEP PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_include_directories(M4OEP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(M4OEP PRIVATE
    keyboard.cpp
	main.cpp
	main_viewport.cpp
)

target_link_libraries(M4OEP PRIVATE
    whale
)
