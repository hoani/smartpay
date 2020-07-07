cmake_minimum_required (VERSION 3.5)

project (CMakeProject)

# Global compile options
if(MSVC)
    add_compile_options("/W4" "/WX" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-O3>")
endif()

#set(source_dir  "${PROJECT_SOURCE_DIR}/src/")
add_subdirectory(src)

add_executable(App ./main.c)

target_link_libraries(App PRIVATE Server Api)

target_compile_features(App PRIVATE c_std_11)

add_subdirectory(test)

