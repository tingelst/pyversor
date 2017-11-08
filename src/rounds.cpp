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

#include <pyversor/rounds.h>

namespace pyversor {

namespace cga {

void def_rounds(py::module &m) {
  using vsr::cga::Round;
  auto t = m.def_submodule("rounds");
  round::def_null<ega::vector_t>(t);
  round::def_null<cga::vector_t>(t);
  round::def_distance<vector_t>(t);
  round::def_squared_distance<vector_t>(t);
  round::def_radius_center_location<dual_sphere_t>(t);
  round::def_radius_center_location<sphere_t>(t);
  round::def_radius_center_location<point_pair_t>(t);
  round::def_radius_center_location<circle_t>(t);

  round::def_normalize<dual_sphere_t>(t);
  round::def_normalize<sphere_t>(t);
  round::def_normalize<point_pair_t>(t);
  round::def_normalize<circle_t>(t);

  round::def_size<dual_sphere_t, true>(t);
  round::def_size<sphere_t, false>(t);
  round::def_size<point_pair_t, true>(t);
  round::def_size<circle_t, false>(t);

  round::def_carrier<point_pair_t>(t);
  round::def_carrier<circle_t>(t);
  round::def_surround<point_pair_t>(t);
  round::def_surround<circle_t>(t);
  round::def_renormalize<point_pair_t>(t);
  round::def_renormalize<circle_t>(t);
  round::def_direction<point_pair_t>(t);
  round::def_direction<circle_t>(t);
  round::def_split<point_pair_t>(t);
  round::def_split<circle_t>(t);

  round::def_produce<vector_t>(t);
}

} // namespace cga

} // namespace pyversor
