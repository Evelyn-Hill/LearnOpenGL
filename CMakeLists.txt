cmake_minimum_required(VERSION 4.0)

project(OpenGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES 
	"src/*.cpp"
	"src/*.hpp"
	"src/*.c"
	"src/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(external/glfw)
add_subdirectory(external/spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC
	external/glfw/include 
	external/spdlog/include 
	${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw spdlog)

# Move compile commands to root directory if they exist
if(EXISTS build/compile_commands.json)
	file(COPY_FILE build/compile_commands.json ./compile_commands.json)
endif()

