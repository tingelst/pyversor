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

#include <pyversor/c3d/flats.h>

namespace pyversor {

namespace c3d {

void def_flats(py::module &m) {
  auto flats = m.def_submodule("flats");
  def_flat_point(flats);
  def_dual_line(flats);
  def_line(flats);
  def_dual_plane(flats);
  def_plane(flats);
}

void def_flat_point(py::module &m) {
  auto flp = def_multivector<c3d::flat_point_t>(m, "FlatPoint");
  flp.def(py::init([](const c3d::point_t &p) {
    return new c3d::flat_point_t(p.null() ^ c3d::infinity_t(1.0));
  }));
  //   def_geometric_product<c3d::flat_point_t, c3d::flat_point_t>(flp);
}

void def_dual_line(py::module &m) {
  auto dll = def_multivector<c3d::dual_line_t>(m, "DualLine");
  dll.def(py::init<double, double, double, double, double, double>());
  def_geometric_product<c3d::dual_line_t, c3d::dual_line_t>(dll);
  def_geometric_product<c3d::dual_line_t, c3d::motor_t>(dll);
  def_addition<c3d::dual_line_t, c3d::motor_t>(dll);
}

void def_line(py::module &m) {
  auto lin = def_multivector<c3d::line_t>(m, "Line");
  lin.def(py::init<double, double, double, double, double, double>());
  lin.def(py::init([](const c3d::point_t &p, const c3d::point_t &q) {
    return new c3d::line_t(p.null() ^ q.null() ^ c3d::infinity_t(1.0));
  }));
  def_geometric_product<c3d::line_t, c3d::line_t>(lin);
}

void def_dual_plane(py::module &m) {
  auto dlp = def_multivector<c3d::dual_plane_t>(m, "DualPlane");
  dlp.def(py::init<double, double, double, double>());
  def_geometric_product<c3d::dual_plane_t, c3d::dual_plane_t, motor_t>(dlp);
}

void def_plane(py::module &m) {
  auto pln = def_multivector<c3d::plane_t>(m, "Plane");
  pln.def(py::init(
      [](const c3d::point_t &p, const c3d::point_t &q, const c3d::point_t &r) {
        return new c3d::plane_t(p.null() ^ q.null() ^ r.null() ^
                                c3d::infinity_t(1.0));
      }));
  pln.def(py::init<double, double, double, double>());
  def_geometric_product<c3d::plane_t, c3d::plane_t, motor_t>(pln);
}

} // namespace c3d

} // namespace pyversor
