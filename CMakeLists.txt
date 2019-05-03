cmake_minimum_required (VERSION 2.6)
project (I3DAssignment2)

set(GAME_SRC
  src/main.cpp)

set(GAME_HEADERS
  src/main.h)

add_executable(Frogger ${GAME_SRC} ${GAME_HEADERS})
