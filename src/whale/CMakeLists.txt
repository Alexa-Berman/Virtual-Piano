add_library(whale STATIC)

target_compile_features(whale PUBLIC cxx_std_23)

target_link_libraries(whale PUBLIC
    glad::glad
    glm::glm
    glfw
    OpenGL::GL
)

add_subdirectory(core)
add_subdirectory(platform)

target_compile_definitions(whale PUBLIC PROJECT_ROOT="${PROJECT_SOURCE_DIR}")

if(PLATFORM_OPENGL)
    target_compile_definitions(whale PUBLIC PLATFORM_OPENGL="${PLATFORM_OPENGL}")
endif()
