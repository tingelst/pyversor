cmake_minimum_required(VERSION 2.8.12)
project(pyversor)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -ftemplate-depth-1200")


include_directories(
  include
  versor/include/vsr
  versor/include/vsr/space
  versor/include/vsr/util
  )

add_subdirectory(pybind11)

file(GLOB core versor/src/space/*.cpp)
pybind11_add_module(pyversor
  src/versor_pybind11.cpp
  src/versor_vector_pybind11.cpp
  # src/versor_bivector_pybind11.cpp
  # src/versor_rotor_pybind11.cpp
  ${core}
)
