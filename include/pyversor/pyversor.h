// Copyright (c) 2015, Lars Tingelstad
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of pyversor nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <versor/space/cga3D_op.h>
#include <versor/space/cga3D_types.h>

namespace py = pybind11;

using cga_t = vsr::algebra<vsr::metric<4, 1, true>, double>;
using grade_0 = cga_t::make_grade<0>;
using grade_1 = cga_t::make_grade<1>;
using grade_2 = cga_t::make_grade<2>;
using grade_3 = cga_t::make_grade<3>;
using grade_4 = cga_t::make_grade<4>;
using grade_5 = cga_t::make_grade<5>;

template <typename T>
py::class_<T> add(py::module &m, const std::string &name) {
  auto t = py::class_<T>(m, name.c_str(), py::buffer_protocol());
  t.def(py::init([](py::buffer b) {
    py::buffer_info info = b.request();
    auto v = new T();
    memcpy(v, info.ptr, sizeof(double) * v->Num);
    return v;
  }));
  t.def("grade", [](const T &arg, int grade) {
    switch (grade) {
      case 0:
        return T(grade_0(arg));
      case 1:
        return T(grade_1(arg));
      case 2:
        return T(grade_2(arg));
      case 3:
        return T(grade_3(arg));
      case 4:
        return T(grade_4(arg));
      case 5:
        return T(grade_5(arg));
      default:
        throw std::invalid_argument("Can only project onto grades 0 to 5.");
    };
  });
  t.def("__neg__", [](const T &arg) { return -arg; });
  t.def("__mul__", [](const T &lhs, double rhs) { return lhs * rhs; });
  t.def("__rmul__", [](const T &lhs, double rhs) { return lhs * rhs; });
  t.def("__imul__", [](T &lhs, double rhs) { return lhs *= rhs; });
  t.def("__add__", [](const T &lhs, const T &rhs) { return lhs + rhs; });
  t.def("__radd__", [](const T &lhs, double rhs) { return lhs + rhs; });
  t.def("__sub__", [](const T &lhs, const T &rhs) { return lhs - rhs; });
  t.def("__xor__", [](const T &lhs, const T &rhs) { return lhs ^ rhs; });
  t.def("__le__", [](const T &lhs, const T &rhs) { return lhs <= rhs; });
  t.def("dual", &T::dual);
  t.def("duale", &T::duale);
  t.def("undual", &T::undual);
  t.def("unduale", &T::unduale);
  t.def("__getitem__", [](T &arg, int idx) { return arg[idx]; });
  t.def("__setitem__", [](T &arg, int idx, double val) { arg[idx] = val; });
  t.def("__repr__", [name](const T &arg) {
    std::stringstream ss;
    ss.precision(4);
    ss << name << "([";
    for (int i = 0; i < arg.Num - 1; ++i) {
      ss << arg[i] << ", ";
    }
    ss << arg[arg.Num - 1] << "])";
    return ss.str();
  });
  t.def_buffer([](T &arg) {
    return py::buffer_info(
        &arg.val[0], sizeof(double), py::format_descriptor<double>::format(), 1,
        {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
  });
  return t;
}