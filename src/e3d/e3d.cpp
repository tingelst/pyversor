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

namespace e3d {

void def_submodule(py::module &m) {
  auto ega = m.def_submodule("e3d");
  def_vector(ega);
  def_bivector(ega);
  def_trivector(ega);
  def_rotator(ega);
  def_full_multivector(ega);
}

void def_vector(py::module &m) {
  auto vec = def_multivector<e3d::vector_t>(m, "Vector");
  vec.def(py::init<double, double, double>());
  def_geometric_product<e3d::vector_t, e3d::vector_t>(vec);
  def_outer_product<e3d::vector_t, e3d::vector_t>(vec);
}

void def_bivector(py::module &m) {
  auto biv = def_multivector<e3d::bivector_t>(m, "Bivector");
  biv.def(py::init<double, double, double>());
  def_geometric_product<e3d::bivector_t, e3d::bivector_t>(biv);
}

void def_trivector(py::module &m) {
  auto tri = def_multivector<e3d::trivector_t>(m, "Trivector");
  tri.def(py::init<double>());
}

void def_rotator(py::module &m) {
  auto rot = def_multivector<e3d::rotator_t>(m, "Rotator");
  rot.def(py::init<double, double, double, double>());
}

void def_full_multivector(py::module &m) {
  auto mv = def_multivector<e3d::multivector_t>(m, "Multivector");
  mv.def(py::init<double, double, double, double, double, double, double,
                  double>());
  def_geometric_product<e3d::multivector_t, e3d::multivector_t>(mv);
  def_outer_product<e3d::multivector_t, e3d::multivector_t>(mv);
}

} // namespace e3d

} // namespace pyversor