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

pybind11_add_module(pyversor
  src/versor_pybind11.cpp
  src/versor_vector_pybind11.cpp
  src/versor_bivector_pybind11.cpp
  src/versor_rotor_pybind11.cpp
  #src/versor_point_pybind11.cpp
  #src/versor_line_pybind11.cpp
  #src/versor_dual_line_pybind11.cpp
  #src/versor_translator_pybind11.cpp
  #src/versor_motor_pybind11.cpp
  #src/versor_dual_plane_pybind11.cpp
  #src/versor_plane_pybind11.cpp
  #src/versor_circle_pybind11.cpp
  #src/versor_point_pair_pybind11.cpp
  #src/versor_sphere_pybind11.cpp
  #src/versor_conformal_geometric_algebra_pybind11.cpp
  #src/versor_euclidean_geometric_algebra_pybind11.cpp
)
target_link_libraries(pyversor PRIVATE versor)
