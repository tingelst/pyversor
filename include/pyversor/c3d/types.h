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

namespace c3d {

using scalar_t = cga_t::make_grade<0>;
using vector_t = cga_t::make_grade<1>;
using point_t = vector_t;
using dual_sphere_t = vector_t;
using bivector_t = cga_t::make_grade<2>;
using point_pair_t = bivector_t;
using trivector_t = cga_t::make_grade<3>;
using circle_t = trivector_t;
using quadvector_t = cga_t::make_grade<4>;
using sphere_t = quadvector_t;
using pseudoscalar_t = vsr::cga::Pss;
using motor_t = vsr::cga::Mot;
using translator_t = vsr::cga::Trs;
using conformal_rotor_t = vsr::cga::Con;
using boost_t = vsr::cga::Bst;
using dual_line_t = vsr::cga::Dll;
using line_t = vsr::cga::Lin;
using dual_plane_t = vsr::cga::Dlp;
using flat_point_t = vsr::cga::Flp;
using plane_t = vsr::cga::Pln;
using direction_vector_t = vsr::cga::Drv;
using direction_bivector_t = vsr::cga::Drb;
using direction_trivector_t = vsr::cga::Drt;
using tangent_vector_t = vsr::cga::TangentVector;
using tangent_bivector_t = vsr::cga::TangentBivector;
using tangent_trivector_t = vsr::cga::TangentTrivector;
using origin_t = vsr::cga::Ori;
using infinity_t = vsr::cga::Inf;
using multivector_t =
    vsr::Multivector<cga_t, vsr::Basis<0, 1, 2, 4, 8, 16, 3, 5, 6, 9, 10, 12,
                                       17, 18, 20, 24, 7, 11, 13, 14, 19, 21,
                                       22, 25, 26, 28, 15, 23, 27, 29, 30, 31>>;

} // namespace cga

} // namespace pyversor