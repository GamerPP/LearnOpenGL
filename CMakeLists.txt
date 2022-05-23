cmake_minimum_required(VERSION 3.20.0)
project(OpenGL VERSION 0.1.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/src/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glew)
add_subdirectory(external/glm)

target_include_directories(${PROJECT_NAME} PUBLIC 
    external/glfw/include 
    external/glew/include 
    external/imgui
    external/glm
    external)

file(GLOB IMGUI_SOURCE "external/imgui/*.cpp" "external/imgui/backends/imgui_impl_glfw.cpp" "external/imgui/backends/imgui_impl_opengl3.cpp")
add_library(imgui ${IMGUI_SOURCE})
target_include_directories(imgui PRIVATE 
    external/imgui
    external/glfw/include)

target_link_directories(${PROJECT_NAME} PRIVATE 
    external/glfw/src
    external/glew/build)

target_link_libraries(${PROJECT_NAME} glfw libglew_static GL imgui)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   rm -r $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   copy_directory ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources)
