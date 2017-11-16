cmake_minimum_required(VERSION 3.2)
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
  src/e3d/e3d.cpp
  src/c3d/c3d.cpp
  src/c3d/rounds.cpp
  src/c3d/flats.cpp
  src/c3d/multivectors.cpp
  src/c3d/tangents.cpp
  src/c3d/directions.cpp
  src/c3d/versors.cpp
  src/c3d/generate.cpp
  src/c3d/construct.cpp
  src/c3d/operate.cpp
  src/c3d/vsr_cga3D_op.cpp
  src/c3d/vsr_cga3D_round.cpp
  src/c2d/c2d.cpp
  src/sta/sta.cpp
)
