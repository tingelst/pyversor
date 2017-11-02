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
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <versor/space/cga3D_op.h>
#include <versor/space/cga3D_round.h>
#include <versor/space/cga3D_types.h>

namespace pyversor {

namespace py = pybind11;

using cga_t = vsr::algebra<vsr::metric<4, 1, true>, double>;

namespace ega {

using scalar_t = vsr::NSca<5>;
using vector_t = vsr::NVec<5>;
using bivector_t = vsr::NBiv<5>;
using trivector_t = vsr::NTri<5>;
using rotator_t = vsr::NRot<5>;
using multivector_t =
    vsr::Multivector<cga_t, vsr::Basis<0, 1, 2, 4, 3, 5, 6, 7>>;

} // namespace ega

namespace cga {

using scalar_t = cga_t::make_grade<0>;
using vector_t = cga_t::make_grade<1>;

struct point_t : vector_t {
  point_t(const vector_t &v) : vector_t(v.null()) {}
  point_t(const ega::vector_t &v) : vector_t(v.null()) {}
  point_t(double x, double y, double z)
      : vector_t(ega::vector_t(x, y, z).null()) {}
};

struct dual_sphere_t : vector_t {
  dual_sphere_t(const vector_t &v) : vector_t(v) {}
  dual_sphere_t(const point_t &p, double r)
      : vector_t(vsr::cga::Construct::sphere(p, r).dual()) {}
  dual_sphere_t(double x, double y, double z, double r)
      : dual_sphere_t(point_t(x, y, z), r) {}
};

using bivector_t = cga_t::make_grade<2>;
struct point_pair_t : bivector_t {
  point_pair_t(const bivector_t &b) : bivector_t(b) {}
  point_pair_t(const point_t &a, const point_t &b) : bivector_t(a ^ b) {}
};

using trivector_t = cga_t::make_grade<3>;
struct circle_t : trivector_t {
  circle_t(const trivector_t &t) : trivector_t(t) {}
  circle_t(const point_t &a, const point_t &b, const point_t &c)
      : trivector_t(a ^ b ^ c) {}
};

using quadvector_t = cga_t::make_grade<4>;

struct sphere_t : quadvector_t {
  sphere_t(const quadvector_t &v) : quadvector_t(v) {}
  sphere_t(const point_t &p, double r)
      : sphere_t(vsr::cga::Construct::sphere(p, r)) {}
  sphere_t(double x, double y, double z, double r)
      : sphere_t(point_t(x, y, z), r) {}
  sphere_t(const point_t &a, const point_t &b, const point_t &c,
           const point_t &d)
      : sphere_t(a ^ b ^ c ^ d) {}
};

using pseudoscalar_t = vsr::cga::Pss;
using motor_t = vsr::cga::Mot;
using dual_line_t = vsr::cga::Dll;
using line_t = vsr::cga::Lin;
using dual_plane_t = vsr::cga::Dlp;
using flat_point_t = vsr::cga::Flp;
using plane_t = vsr::cga::Pln;
using direction_vector_t = vsr::cga::Drv;
using direction_bivector_t = vsr::cga::Drb;
using direction_trivector_t = vsr::cga::Drt;
using origin_t = vsr::cga::Ori;
using infinity_t = vsr::cga::Inf;
using multivector_t =
    vsr::Multivector<cga_t, vsr::Basis<0, 1, 2, 4, 8, 16, 3, 5, 6, 9, 10, 12,
                                       17, 18, 20, 24, 7, 11, 13, 14, 19, 21,
                                       22, 25, 26, 28, 15, 23, 27, 29, 30, 31>>;
} // namespace cga

template <typename T> struct outer_product {
  template <typename A, typename module_t> static void add(module_t &m) {
    m.def("__xor__", [](const T &lhs, const A &rhs) { return lhs ^ rhs; });
    m.def("outer", [](const T &lhs, const A &rhs) { return lhs ^ rhs; });
  }

  template <typename A, typename B, typename... Cs, typename module_t>
  static void add(module_t &m) {
    add<A>(m);
    add<B, Cs...>(m);
  }
};

template <typename T>
py::class_<T> add_multivector(py::module &m, const std::string &name) {
  auto t = py::class_<T>(m, name.c_str(), py::buffer_protocol());
  // negate
  t.def("__neg__", [](const T &arg) { return -arg; });
  // reverse
  t.def("__invert__", [](const T &arg) { return ~arg; });
  t.def("reverse", [](const T &arg) { return ~arg; });
  // inverse
  t.def("inverse", [](const T &arg) { return !arg; });
  // involution
  t.def("involute", &T::conjugation);
  // conjugation
  t.def("conjugate", &T::conjugation);
  // geometric product
  //   t.def("geometric", [](const T &lhs, const T &rhs) { return lhs * rhs; });
  //   t.def("__mul__", [](const T &lhs, const T &rhs) { return lhs * rhs; });
  //   t.def("__mul__", [](const T &lhs, double rhs) { return lhs * rhs; });
  //   t.def("__rmul__", [](const T &lhs, double rhs) { return lhs * rhs; });
  //   t.def("__imul__", [](T &lhs, double rhs) { return lhs *= rhs; });
  // division
  //   t.def("__div__", [](const T &lhs, const T &rhs) { return lhs / rhs; });
  //   t.def("__div__", [](const T &lhs, double rhs) { return lhs / rhs; });
  //   t.def("__idiv__", [](T &lhs, const T &rhs) { return lhs /= rhs; });
  //   t.def("__idiv__", [](T &lhs, double rhs) { return lhs /= rhs; });
  // addition
  //   t.def("__add__", [](const T &lhs, const T &rhs) { return lhs + rhs; });
  //   t.def("__iadd__", [](T &lhs, const T &rhs) { return lhs += rhs; });
  // subtraction
  //   t.def("__sub__", [](const T &lhs, const T &rhs) { return lhs - rhs; });
  //   t.def("__sub__", [](const T &lhs, double rhs) { return lhs + (rhs *
  //   -1.0); }); t.def("__isub__", [](T &lhs, const T &rhs) { return lhs -=
  //   rhs; }); t.def("__rsub__",
  //         [](const T &lhs, double rhs) { return lhs + (rhs * -1.0); });
  // outer product
  //   t.def("outer", [](const T &lhs, const T &rhs) { return lhs ^ rhs; });
  //   t.def("outer", [](const T &lhs, double rhs) { return lhs * rhs; });
  //   t.def("__xor__", [](const T &lhs, const T &rhs) { return lhs ^ rhs; });
  //   t.def("__xor__", [](const T &lhs, double rhs) { return lhs * rhs; });
  //   t.def("__rxor__", [](const T &lhs, double rhs) { return lhs * rhs; });
  // inner product
  //   t.def("inner", [](const T &lhs, const T &rhs) { return (lhs <= rhs)[0];
  //   }); t.def("__le__", [](const T &lhs, const T &rhs) { return (lhs <=
  //   rhs)[0]; });
  // commutator products
  //   t.def("commutator", [](const T &lhs, const T &rhs) { return lhs % rhs;
  //   }); t.def("anti_commutator", [](const T &lhs, const T &rhs) {
  //     return (lhs * rhs + rhs * lhs) * 0.5;
  //   });
  // sandwich product
  //   t.def("spin",
  //         [](const T &lhs, const ega::rotator_t &rhs) { return lhs.spin(rhs);
  //         });
  //   t.def("spin",
  //         [](const T &lhs, const cga::motor_t &rhs) { return lhs.spin(rhs);
  //         });
  // reflect
  //   t.def("reflect", [](const T &lhs, const T &rhs) { return
  //   lhs.reflect(rhs); });
  // weights, units and norms
  //   t.def("weight", &T::wt);
  //   t.def("rweight", &T::rwt);
  //   t.def("norm", &T::norm);
  //   t.def("rnorm", &T::rnorm);
  //   t.def("unit", &T::unit);
  //   t.def("runit", &T::runit);
  //   t.def("tunit", &T::tunit);
  // Get scalar coefficient
  t.def("__getitem__", [](T &arg, int idx) { return arg[idx]; });
  // Set scalar coefficient
  t.def("__setitem__", [](T &arg, int idx, double val) { arg[idx] = val; });
  // Representation string
  t.def("__repr__", [name](const T &arg) {
    std::stringstream ss;
    ss.precision(4);
    ss << name << "(";
    for (int i = 0; i < arg.Num - 1; ++i) {
      ss << arg[i] << ", ";
    }
    ss << arg[arg.Num - 1] << ")";
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
  //   t.def(py::pickle(
  //       [](const T &p) { // __getstate__
  //         std::vector<double> coeffs;
  //         for (size_t i = 0; i < T::Num; ++i) {
  //           coeffs.push_back(p[i]);
  //         }
  //         return coeffs;
  //       },
  //       [](const std::vector<double> &coeffs) { // __setstate__
  //         if (coeffs.size() != T::Num) {
  //           throw std::runtime_error("Invalid state!");
  //         }
  //         // Create a new C++ instance
  //         T p;
  //         for (size_t i = 0; i < T::Num; ++i) {
  //           p[i] = coeffs[i];
  //         }
  //         return p;
  //       }));
  return t;
}

template <typename T>
py::class_<T> add_euclidean_multivector(py::module &m,
                                        const std::string &name) {
  auto t = add_multivector<T>(m, name);
  t.def("grade", [](const T &arg, int grade) {
    switch (grade) {
    case 0:
      return T(ega::scalar_t(arg));
    case 1:
      return T(ega::vector_t(arg));
    case 2:
      return T(ega::bivector_t(arg));
    case 3:
      return T(ega::trivector_t(arg));
    default:
      throw std::invalid_argument("Can only project onto grades 0 to 3.");
    };
  });
  t.def("dual", &T::duale);
  t.def("undual", &T::unduale);
  return t;
}

template <typename T>
py::class_<T> add_conformal_multivector(py::module &m,
                                        const std::string &name) {
  auto t = add_multivector<T>(m, name);
  //   t.def("grade", [](const T &arg, int grade) {
  //     switch (grade) {
  //     case 0:
  //       return T(cga::scalar_t(arg));
  //     case 1:
  //       return T(cga::vector_t(arg));
  //     case 2:
  //       return T(cga::bivector_t(arg));
  //     case 3:
  //       return T(cga::trivector_t(arg));
  //     case 4:
  //       return T(cga::quadvector_t(arg));
  //     case 5:
  //       return T(cga::pseudoscalar_t(arg));
  //     default:
  //       throw std::invalid_argument("Can only project onto grades 0 to 5.");
  //     };
  //   });
  t.def("dual", &T::dual);
  t.def("undual", &T::undual);
  return t;
}

} // namespace pyversor