cmake_minimum_required (VERSION 2.8)
project (SmithGame)
set(SmithGame_VERSION_MAJOR 1)

if(UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

file(GLOB MySources
	src/*.h
	src/*.cpp
)

file(GLOB MySourcesGame
	src/game/*.h
	src/game/*.cpp
)

file(GLOB MySourcesScene
	src/scene/*.h
	src/scene/*.cpp
)

file(GLOB MySourcesAsset
	src/asset/*.h
	src/asset/*.cpp
)

file(GLOB MySourcesRendering
	src/rendering/*.h
	src/rendering/*.cpp
)

file(GLOB MySourcesRenderingShaders
	src/rendering/shaders/*.h
	src/rendering/shaders/*.cpp
)

add_executable(SmithGame ${MySources} ${MySourcesGame} ${MySourcesScene} ${MySourcesAsset} ${MySourcesRendering} ${MySourcesRenderingShaders})

target_include_directories(SmithGame PUBLIC "${CMAKE_SOURCE_DIR}/src")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(SmithGame ${GLFW_STATIC_LIBRARIES})

target_link_libraries(SmithGame "SDL2")
target_link_libraries(SmithGame "GLEW")
target_link_libraries(SmithGame "sfml-system")
target_link_libraries(SmithGame "sfml-graphics")
target_link_libraries(SmithGame "GL")
