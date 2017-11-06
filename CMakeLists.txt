cmake_minimum_required(VERSION 3.6)
project(pyversor LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -ftemplate-depth-1200")

include_directories(
  include
  include/versor
  include/versor/space
  include/versor/util
  )

add_subdirectory(pybind11)

pybind11_add_module(__pyversor__
  src/pyversor.cpp
  #src/pyversor_ega.cpp
  src/pyversor_cga.cpp
  src/rounds.cpp
  src/flats.cpp
  src/multivectors.cpp
  src/tangents.cpp
  src/directions.cpp
  src/versors.cpp
  src/generate.cpp
  src/vsr_cga3D_op.cpp
  src/vsr_cga3D_round.cpp
)
