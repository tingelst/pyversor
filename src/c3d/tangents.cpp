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

#include <pyversor/c3d/tangents.h>

namespace pyversor {

namespace c3d {

void def_tangents(py::module &m) {
  auto tangents = m.def_submodule("tangents");
  def_tangent_vector(tangents);
  def_tangent_bivector(tangents);
  def_tangent_trivector(tangents);
}

void def_tangent_vector(py::module &m) {
  auto tnv = def_multivector<c3d::tangent_vector_t>(m, "TangentVector");
  tnv.def(py::init<double, double, double>());
  def_sandwich_product<c3d::tangent_vector_t, c3d::translator_t,
                       c3d::bivector_t>(tnv);
}
void def_tangent_bivector(py::module &m) {
  auto tnb = def_multivector<c3d::tangent_bivector_t>(m, "TangentBivector");
  tnb.def(py::init<double, double, double>());
}

void def_tangent_trivector(py::module &m) {
  auto tnt = def_multivector<c3d::tangent_trivector_t>(m, "TangentTrivector");
  tnt.def(py::init<double>());
}

} // namespace c3d

} // namespace pyversor
