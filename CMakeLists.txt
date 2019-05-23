cmake_minimum_required (VERSION 2.6)
project (I3DAssignment2)

set(GAME_MAIN
  src/main.cpp)

#source & headers
set(GAME_SRC
	src/camera/camera.cpp
  src/vector/vector.cpp
  src/time/time.cpp

  src/keyboard/keyboard.c
  src/keyboard/keyboard.cpp

  src/shape/primitives/primitives.cpp
  src/shape/primitives/function/function.cpp

  src/material/material.cpp
	)

set(GAME_HEADERS
  src/main.h
  src/camera/camera.h
  src/vector/vector.h
  src/time/time.h

  src/keyboard/keyboard.hpp
  src/keyboard/keyboard.h

  src/shape/primitives/primitives.hpp
  src/shape/primitives/function/function.hpp
  src/shape/shape.hpp

  src/material/material.hpp
	)

set(GAME_TESTS
  src/vector/vector.test.cpp

  src/shape/primitives/primitives.test.cpp
  src/testmain.cpp)


set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/")

add_executable(Frogger ${GAME_SRC} ${GAME_HEADERS} ${GAME_MAIN})

find_package( Boost 1.40 COMPONENTS unit_test_framework REQUIRED )


add_executable(test_executable ${GAME_TESTS} ${GAME_SRC} ${GAME_HEADERS})

target_include_directories(test_executable PRIVATE ${Boost_INCLUDE_DIR} )


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_include_directories(Frogger PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_include_directories(test_executable PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(test_executable
	m
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARY}
  ${Boost_LIBRARIES}
	)

target_link_libraries(Frogger
	m
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARY}
	)
