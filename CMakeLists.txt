cmake_minimum_required (VERSION 2.6)
project (I3DAssignment2)

#source & headers
file(GLOB_RECURSE GAME_SRC
	${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/src/*.c
	)
file(GLOB_RECURSE GAME_HEADERS
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/src/*.h
	)

add_executable(Frogger ${GAME_SRC} ${GAME_HEADERS})
