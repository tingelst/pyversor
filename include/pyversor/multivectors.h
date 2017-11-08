// Copyright (c) 2015, Lars Tingelstad
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of pyversor nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <pyversor/products.h>
#include <pyversor/types.h>

namespace pyversor {

template <typename T> static constexpr auto estrings() {
  auto arr = T::basis::array;
  auto earr = std::array<std::string, arr.size()>{};
  auto size = arr.size();
  for (int i = 0; i < arr.size(); ++i) {
    earr[i] = vsr::bits::estring(arr[i]);
  }
  return earr;
}

template <typename T>
py::class_<T> def_multivector(py::module &m, const std::string &name) {
  auto t =
      py::class_<T>(m, name.c_str(), py::buffer_protocol(), py::dynamic_attr());
  // Constructor from other T
  t.def(py::init<>());
  t.def(py::init<T>());
  // Multiply by double
  def_geometric_product<T, double>(t);
  // Addition of same type
  def_addition<T, T>(t);
  // Subtraction of same type
  def_subtraction<T, T>(t);
  // Negate
  t.def("__neg__", [](const T &arg) { return -arg; });
  // Reverse
  t.def("__invert__", [](const T &arg) { return ~arg; });
  t.def("reverse", [](const T &arg) { return ~arg; });
  // Inverse
  t.def("inverse", [](const T &arg) { return !arg; });
  // Involution
  t.def("involute", &T::involution);
  // Conjugation
  t.def("conjugate", &T::conjugation);
  // Conformal dual
  t.def("dual", &T::dual);
  // Conformal undual
  t.def("undual", &T::undual);
  // Euclidean dual
  t.def("duale", &T::duale);
  // Euclidean undual
  t.def("unduale", &T::unduale);
  // Weights, units and norms
  t.def("weight", &T::wt);
  t.def("rweight", &T::rwt);
  t.def("norm", &T::norm);
  t.def("rnorm", &T::rnorm);
  t.def("unit", &T::unit);
  t.def("runit", &T::runit);
  t.def("tunit", &T::tunit);
  // Grade projection operator
  t.def("grade", [](const T &arg, int grade) {
    switch (grade) {
    case 0:
      return T(cga::scalar_t(arg));
    case 1:
      return T(cga::vector_t(arg));
    case 2:
      return T(cga::bivector_t(arg));
    case 3:
      return T(cga::trivector_t(arg));
    case 4:
      return T(cga::quadvector_t(arg));
    case 5:
      return T(cga::pseudoscalar_t(arg));
    default:
      throw std::invalid_argument("Can only project onto grades 0 to 5.");
    };
  });
  // Get scalar coefficient
  t.def("__getitem__", [](T &arg, int idx) { return arg[idx]; });
  // Set scalar coefficient
  t.def("__setitem__", [](T &arg, int idx, double val) { arg[idx] = val; });
  // List of basis blades
  t.def_property_readonly_static("_basis_blades",
                                 [](py::object) { return estrings<T>(); });
  // Representation string
  t.def("__repr__", [name](const T &arg) {
    auto es = estrings<T>();
    std::stringstream ss;
    ss.precision(4);
    ss << name << " [ ";
    for (int i = 0; i < arg.Num - 1; ++i) {
      ss << arg[i] << " ";
    }
    ss << arg[arg.Num - 1] << "]";
    return ss.str();
  });
  t.def("toarray", [](const T &arg) {
    auto array = py::array_t<double>(T::Num);
    auto buffer = array.request();
    auto ptr = reinterpret_cast<double *>(buffer.ptr);
    for (size_t i = 0; i < T::Num; ++i) {
      ptr[i] = arg[i];
    }
    return array;
  });
  t.def_buffer([](T &arg) {
    return py::buffer_info(
        &arg.val[0], sizeof(double), py::format_descriptor<double>::format(), 1,
        {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
  });
  t.def(py::pickle(
      [](const T &p) { // __getstate__
        std::vector<double> coeffs;
        for (size_t i = 0; i < T::Num; ++i) {
          coeffs.push_back(p[i]);
        }
        return coeffs;
      },
      [](const std::vector<double> &coeffs) { // __setstate__
        if (coeffs.size() != T::Num) {
          throw std::runtime_error("Invalid state!");
        }
        // Create a new C++ instance
        T p;
        for (size_t i = 0; i < T::Num; ++i) {
          p[i] = coeffs[i];
        }
        return p;
      }));
  return t;
}

namespace cga {
void def_vector(py::module &m);
void def_bivector(py::module &m);
void def_trivector(py::module &m);
void def_quadvector(py::module &m);
void def_pseudoscalar(py::module &m);
void def_infinity(py::module &m);
void def_origin(py::module &m);
void def_full_multivector(py::module &m);
} // namespace cga

} // namespace pyversor