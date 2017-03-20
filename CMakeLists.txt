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
  src/versor_bivector_pybind11.cpp
  src/versor_rotor_pybind11.cpp
  src/versor_point_pybind11.cpp
  src/versor_line_pybind11.cpp
  src/versor_dual_line_pybind11.cpp
  src/versor_translator_pybind11.cpp
  src/versor_motor_pybind11.cpp
  src/versor_dual_plane_pybind11.cpp
  src/versor_plane_pybind11.cpp
  src/versor_circle_pybind11.cpp
  src/versor_sphere_pybind11.cpp
  src/versor_conformal_geometric_algebra_pybind11.cpp
  src/versor_euclidean_geometric_algebra_pybind11.cpp
  ${core}
)
