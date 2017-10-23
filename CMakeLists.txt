cmake_minimum_required(VERSION 3.6)
project(pyversor)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -ftemplate-depth-1200")


include_directories(
  include
  include/versor
  include/versor/space
  include/versor/util
  )

add_subdirectory(pybind11)

add_library(versor SHARED 
  src/vsr_cga3D_op.cpp
  src/vsr_cga3D_round.cpp
)

pybind11_add_module(pyversor_
  src/pyversor.cpp
  src/pyversor_ega.cpp
  src/pyversor_cga.cpp
)
target_link_libraries(pyversor_ PRIVATE versor)
