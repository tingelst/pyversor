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

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <type_traits>

namespace pyversor {

namespace py = pybind11;

template <typename A, typename B, typename module_t>
auto def_addition(module_t &m) {
  m.def("__add__", [](const A &lhs, const B &rhs) { return lhs + rhs; },
        py::is_operator());
  m.def("__iadd__", [](A &lhs, const B &rhs) { return lhs += rhs; },
        py::is_operator());
}

template <typename A, typename module_t> auto def_scalar_addition(module_t &m) {
  m.def("__add__", [](const A &lhs, double rhs) { return lhs + rhs; },
        py::is_operator());
  m.def("__radd__", [](const A &lhs, double rhs) { return lhs + rhs; },
        py::is_operator());
}

template <typename A, typename B, typename C, typename module_t>
auto def_addition(module_t &m) {
  m.def("__add__", [](const A &lhs, const B &rhs) { return C(lhs + rhs); },
        py::is_operator());
  m.def("__iadd__", [](A &lhs, const B &rhs) { return C(lhs += rhs); },
        py::is_operator());
}

template <typename A, typename B, typename module_t>
auto def_subtraction(module_t &m) {
  m.def("__sub__", [](const A &lhs, const B &rhs) { return lhs - rhs; },
        py::is_operator());
  m.def("__sub__", [](A &lhs, const B &rhs) { return lhs -= rhs; },
        py::is_operator());
}

template <typename A, typename B, typename C, typename module_t>
auto def_subtraction(module_t &m) {
  m.def("__sub__", [](const A &lhs, const B &rhs) { return C(lhs - rhs); },
        py::is_operator());
  m.def("__isub__", [](A &lhs, const B &rhs) { return C(lhs -= rhs); },
        py::is_operator());
}

template <typename A, typename B, typename module_t>
auto def_outer_product(module_t &m) {
  m.def("__xor__", [](const A &lhs, const B &rhs) { return lhs ^ rhs; });
  m.def("outer", [](const A &lhs, const B &rhs) { return lhs ^ rhs; });
}

template <typename A, typename B, typename module_t>
auto def_inner_product(module_t &m) {
  m.def("__le__", [](const A &lhs, const B &rhs) { return lhs <= rhs; },
        py::is_operator());
  m.def("inner", [](const A &lhs, const B &rhs) { return lhs <= rhs; },
        py::is_operator());
}

template <typename A, typename B, typename module_t>
auto def_geometric_product(module_t &m) {
  if (std::is_same<B, double>()) {
    m.def("__mul__", [](const A &lhs, double rhs) { return lhs * rhs; },
          py::is_operator());
    m.def("__rmul__", [](const A &lhs, double rhs) { return lhs * rhs; },
          py::is_operator());
    m.def("__imul__", [](A &lhs, double rhs) { return lhs *= rhs; },
          py::is_operator());
  } else {
    m.def("geometric", [](const A &lhs, const B &rhs) { return lhs * rhs; },
          py::is_operator());
    m.def("__mul__", [](const A &lhs, const B &rhs) { return lhs * rhs; },
          py::is_operator());
  }
}

template <typename A, typename B, typename C, typename module_t>
auto def_geometric_product(module_t &m) {
  m.def("geometric", [](const A &lhs, const B &rhs) { return C(lhs * rhs); },
        py::is_operator());
  m.def("__mul__", [](const A &lhs, const B &rhs) { return C(lhs * rhs); },
        py::is_operator());
}

template <typename A, typename B, typename module_t>
auto def_sandwich_product(module_t &m) {
  m.def("spin", [](const A &lhs, const B &rhs) { return lhs.spin(rhs); });
}

template <typename A, typename B, typename C, typename module_t>
auto def_sandwich_product(module_t &m) {
  m.def("spin", [](const A &lhs, const B &rhs) { return C(lhs).spin(rhs); });
}

} // namespace pyversor