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

#include <pybind11/pybind11.h>

#include <versor/space/cga3D_op.h>
#include <versor/space/cga3D_round.h>

#include <pyversor/types.h>

namespace pyversor {

namespace py = pybind11;

namespace cga {

struct round {
  template <typename round_t, typename module_t = py::module>
  static void def_distance(module_t &m) {
    using vsr::cga::Round;
    m.def("distance", [](const round_t &a, const round_t &b) {
      return Round::distance(a, b);
    });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_squared_distance(module_t &m) {
    using vsr::cga::Round;
    m.def("squared_distance", [](const round_t &a, const round_t &b) {
      return Round::squaredDistance(a, b);
    });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_location(module_t &m) {
    using vsr::cga::Round;
    m.def("location", [](const round_t &a) { return Round::location(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_center(module_t &m) {
    using vsr::cga::Round;
    m.def("center", [](const round_t &a) { return Round::center(a); });
  }

  template <typename round_t, bool dual, typename module_t = py::module>
  static void def_size(module_t &m) {
    using vsr::cga::Round;
    m.def("size", [](const round_t &a) { return Round::size(a, dual); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_radius(module_t &m) {
    using vsr::cga::Round;
    m.def("radius", [](const round_t &a) { return Round::radius(a); });
    // Inverse of radius
    m.def("curvature", [](const round_t &a) { return Round::curvature(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_null(module_t &m) {
    using vsr::cga::Round;
    m.def("null", [](const round_t &a) { return Round::null(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_carrier(module_t &m) {
    using vsr::cga::Round;
    m.def("carrier", [](const round_t &a) { return Round::carrier(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_normalize(module_t &m) {
    using vsr::cga::Round;
    m.def("normalize", [](const round_t &a) { return Round::normalize(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_renormalize(module_t &m) {
    using vsr::cga::Round;
    m.def("renormalize",
          [](const round_t &a) { return Round::renormalize(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_surround(module_t &m) {
    using vsr::cga::Round;
    m.def("surround", [](const round_t &a) { return Round::surround(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_direction(module_t &m) {
    using vsr::cga::Round;
    m.def("direction", [](const round_t &a) { return Round::direction(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_split(module_t &m) {
    using vsr::cga::Round;
    m.def("split", [](const round_t &a) { return Round::split(a); });
    m.def("split_location",
          [](const round_t &a) { return Round::splitLocation(a); });
  }

  template <typename round_t = dual_sphere_t, typename module_t = py::module>
  static void def_produce(module_t &m) {
    using vsr::cga::Round;
    m.def("produce", [](const round_t &a, const ega::vector_t &b) {
      return Round::produce(a, b);
    });
    m.def("produce", [](const round_t &a, const ega::bivector_t &b) {
      return Round::produce(a, b);
    });
  }

  template <typename round_t, typename module_t = py::module>
  static void def_radius_center_location(module_t &m) {
    def_radius<round_t>(m);
    def_center<round_t>(m);
    def_location<round_t>(m);
  }
};

void def_rounds(py::module &m);

} // namespace cga

} // namespace pyversor
