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

#include <pyversor/multivectors.h>
#include <pyversor/products.h>

namespace pyversor {

namespace cga {

void def_vector(py::module &m) {
  auto vec = def_multivector<cga::vector_t>(m, "Vector");
  vec.def(py::init<double, double, double, double, double>());
  def_geometric_product<cga::vector_t, cga::vector_t>(vec);
}

void def_bivector(py::module &m) {
  auto biv = def_multivector<cga::bivector_t>(m, "Bivector");
  biv.def(py::init<double, double, double, double, double, double, double,
                   double, double, double>());
  biv.def(py::init<cga::dual_line_t>());
  biv.def(py::init<cga::direction_vector_t>());
  biv.def(py::init<cga::tangent_vector_t>());
  def_geometric_product<cga::bivector_t, cga::bivector_t>(biv);
}

void def_trivector(py::module &m) {
  auto tri = def_multivector<cga::trivector_t>(m, "Trivector");
  tri.def(py::init<double, double, double, double, double, double, double,
                   double, double, double>());
  def_geometric_product<cga::trivector_t, cga::trivector_t>(tri);
}

void def_quadvector(py::module &m) {
  auto quad = def_multivector<cga::quadvector_t>(m, "Quadvector");
  quad.def(py::init<double, double, double, double, double>());
  def_geometric_product<cga::quadvector_t, cga::quadvector_t>(quad);
}

void def_pseudoscalar(py::module &m) {
  auto pss = def_multivector<cga::pseudoscalar_t>(m, "Pseudoscalar");
  pss.def(py::init<double>());
}

void def_infinity(py::module &m) {
  auto inf = def_multivector<cga::infinity_t>(m, "Infinity");
  inf.def(py::init<double>());
}

void def_origin(py::module &m) {
  auto ori = def_multivector<cga::origin_t>(m, "Origin");
  ori.def(py::init<double>());
}

void def_full_multivector(py::module &m) {
  def_multivector<multivector_t>(m, "Multivector")
      .def(py::init<>())
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double>());
}

} // namespace cga
} // namespace pyversor