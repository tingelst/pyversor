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
// ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <pyversor/pyversor.h>

namespace pyversor {

namespace ega {

void add_submodule(py::module &m) {
  auto ega = m.def_submodule("ega");
  // add_vector(ega);
  // add_bivector(ega);
  // add_trivector(ega);
  // add_rotator(ega);
  // add_multivector(ega);
  // add_generate(ega);
}

void add_vector(py::module &m) {
  auto t = add_euclidean_multivector<vector_t>(m, "Vector");
  t.def(py::init<double, double, double>());
  t.def("null", &vector_t::null);
  outer_product<vector_t>::add<vector_t, bivector_t>(t);
}

void add_bivector(py::module &m) {
  using vsr::nga::Gen;
  add_euclidean_multivector<bivector_t>(m, "Bivector")
      .def(py::init<double, double, double>())
      .def("__add__",
           [](const bivector_t &a, double b) { return rotator_t(a + b); })
      .def("__radd__",
           [](const bivector_t &a, double b) { return rotator_t(a + b); })
      .def("exp", [](const bivector_t &b) { return Gen::rot(b); });
}

void add_trivector(py::module &m) {
  add_euclidean_multivector<trivector_t>(m, "Trivector")
      .def(py::init<double>());
}

void add_rotator(py::module &m) {
  using vsr::nga::Gen;
  add_euclidean_multivector<rotator_t>(m, "Rotator")
      .def(py::init<double, double, double, double>())
      .def("log", [](const rotator_t &m) { return Gen::log(m); });
}

void add_multivector(py::module &m) {
  add_euclidean_multivector<multivector_t>(m, "Multivector")
      .def(py::init<>())
      .def(py::init<double, double, double, double, double, double, double,
                    double>());
}

void add_generate(py::module &m) {
  using vsr::nga::Gen;
  auto generate = m.def_submodule("generate");
  generate.def("ratio", [](const vector_t &a, const vector_t &b) {
    return vsr::nga::Gen::ratio(a, b);
  });
  generate.def("log", [](const rotator_t &m) { return Gen::log(m); });
  generate.def("exp", [](const bivector_t &b) { return Gen::rot(b); });
}

} // namespace ega

} // namespace pyversor