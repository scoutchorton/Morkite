cmake_minimum_required(VERSION 3.1...3.22) # Most up to date version on Kubuntu 22.04, lower later based on functions used
project(
	Morkite
	VERSION 0.1.0
	LANGUAGES CXX
)

# References:
#   http://derekmolloy.ie/hello-world-introductions-to-cmake/
#   https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/

# Variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
file(GLOB SOURCES "src/*.cpp")

# Packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Lua 5.4 REQUIRED)

# Files
add_executable(morkite ${SOURCES})
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
target_link_libraries(morkite ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${LUA_LIBRARIES})