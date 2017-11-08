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

#include <pyversor/c3d/versors.h>

namespace pyversor {

namespace c3d {

void def_versors(py::module &m) {
  auto versors = m.def_submodule("versors");
  def_rotator(versors);
  def_translator(versors);
  def_motor(versors);
  def_conformal_rotor(versors);
  def_boost(versors);
}

void def_rotator(py::module &m) {
  auto rot = def_multivector<ega::rotator_t>(m, "Rotator");
  def_geometric_product<ega::rotator_t, ega::rotator_t>(rot);
  def_geometric_product<ega::rotator_t, c3d::translator_t>(rot);
  def_geometric_product<ega::rotator_t, c3d::motor_t>(rot);
}

void def_translator(py::module &m) {
  auto trs = def_multivector<c3d::translator_t>(m, "Translator");
  def_geometric_product<c3d::translator_t, c3d::translator_t>(trs);
  def_geometric_product<c3d::translator_t, c3d::motor_t>(trs);
  def_geometric_product<c3d::translator_t, ega::rotator_t>(trs);
}

void def_motor(py::module &m) {
  auto mot = def_multivector<c3d::motor_t>(m, "Motor");
  mot.def(py::init<double, double, double, double, double, double, double,
                   double>());
  mot.def(py::init<c3d::dual_line_t>());
  def_geometric_product<c3d::motor_t, c3d::motor_t>(mot);
  def_geometric_product<c3d::motor_t, c3d::translator_t>(mot);
  def_geometric_product<c3d::motor_t, ega::rotator_t>(mot);
  def_geometric_product<c3d::motor_t, c3d::dual_line_t>(mot);
  def_addition<c3d::motor_t, c3d::dual_line_t>(mot);
}

void def_conformal_rotor(py::module &m) {
  auto con = def_multivector<conformal_rotor_t>(m, "ConformalRotor");
  def_geometric_product<c3d::conformal_rotor_t, c3d::conformal_rotor_t>(con);
}

void def_boost(py::module &m) {
  auto bst = def_multivector<boost_t>(m, "Boost");
  def_geometric_product<c3d::boost_t, c3d::boost_t>(bst);
}

} // namespace c3d

} // namespace pyversor
