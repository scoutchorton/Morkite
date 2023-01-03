cmake_minimum_required(VERSION 3.1...3.22) # Most up to date version on Kubuntu 22.04, lower later based on functions used
project(
	Morkite
	VERSION 0.1.0
	LANGUAGES CXX
)

include(ExternalProject)

# References:
#   http://derekmolloy.ie/hello-world-introductions-to-cmake/
#   https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/

# Variables
file(GLOB CPP_SOURCES "src/*.cpp")

# Packages
if(MSVC)
	# Architecture specific values
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(LUA_DL_ARCH "Win64")
		set(SDL2_ARCH "x64")
	else()
		set(LUA_DL_ARCH "Win32")
		set(SDL2_ARCH "x86")
	endif()

	set(dlls "")

	# Lua (precompiled)
	ExternalProject_Add(lua
		URL "https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/lua-5.4.2_${LUA_DL_ARCH}_dll16_lib.zip/download"
		DOWNLOAD_NAME "lua-5.4.2_${LUA_DL_ARCH}_dll16_lib.zip"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
		DOWNLOAD_EXTRACT_TIMESTAMP TRUE
		BUILD_BYPRODUCTS <SOURCE_DIR>/lua54.dll <SOURCE_DIR>/lua54.lib
	)
	ExternalProject_Get_property(lua SOURCE_DIR)
	set(LUA_INCLUDE_DIRS "${SOURCE_DIR}/include")
	set(LUA_LIBRARIES "${SOURCE_DIR}/lua54.lib")
	list(APPEND dlls "${SOURCE_DIR}/lua54.dll")

	# SDL2 (precompiled)
	ExternalProject_Add(sdl2
		URL "https://github.com/libsdl-org/SDL/releases/download/release-2.26.1/SDL2-devel-2.26.1-VC.zip"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
		DOWNLOAD_EXTRACT_TIMESTAMP TRUE
		BUILD_BYPRODUCTS <SOURCE_DIR>/lib/${SDL2_ARCH}/SDL2.dll <SOURCE_DIR>/lib/${SDL2_ARCH}/SDL2.lib <SOURCE_DIR>/lib/${SDL2_ARCH}/SDL2main.lib
	)
	ExternalProject_Get_property(sdl2 SOURCE_DIR)
	set(SDL2_INCLUDE_DIRS "${SOURCE_DIR}/include")
	set(SDL2_LIBRARIES "${SOURCE_DIR}/lib/${SDL2_ARCH}/SDL2.lib" "${SOURCE_DIR}/lib/${SDL2_ARCH}/SDL2main.lib")
	list(APPEND dlls "${SOURCE_DIR}/lib/${SDL2_ARCH}/SDL2.dll")

	# SDL Image (precompiled)
	ExternalProject_Add(sdl2_image
		URL "https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.2/SDL2_image-devel-2.6.2-VC.zip"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
		DOWNLOAD_EXTRACT_TIMESTAMP TRUE
		BUILD_BYPRODUCTS <SOURCE_DIR>/lib/${SDL2_ARCH}/SDL2_image.dll <SOURCE_DIR>/lib/${SDL2_ARCH}/SDL2_image.lib
	)
	ExternalProject_Get_property(sdl2_image SOURCE_DIR)
	set(SDL2_IMAGE_INCLUDE_DIRS "${SOURCE_DIR}/include")
	set(SDL2_IMAGE_LIBRARIES "${SOURCE_DIR}/lib/${SDL2_ARCH}/SDL2_image.lib")
	list(APPEND dlls "${SOURCE_DIR}/lib/${SDL2_ARCH}/SDL2_image.dll")
else()
	include("${CMAKE_SOURCE_DIR}/cmake/FindSDL2_image.cmake")

	# Find libraries
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	find_package(Lua 5.4 REQUIRED)
endif()

# Compile project
add_executable(morkite)
add_dependencies(morkite lua sdl2 sdl2_image)
include_directories(morkite ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS})
target_link_libraries(morkite ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${LUA_LIBRARIES})
target_sources(morkite PUBLIC ${CPP_SOURCES})

# Copy DLL files to exe directory
if(dlls)
	foreach(dll ${dlls})
		add_custom_command(
			TARGET morkite
			COMMAND ${CMAKE_COMMAND} -E copy "${dll}" "${CMAKE_BINARY_DIR}"
		)
	endforeach()
endif()