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

#pragma once

#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <versor/space/cga3D_op.h>
#include <versor/space/cga3D_round.h>

#include <pyversor/directions.h>
#include <pyversor/flats.h>
#include <pyversor/generate.h>
#include <pyversor/multivectors.h>
#include <pyversor/products.h>
#include <pyversor/rounds.h>
#include <pyversor/tangents.h>
#include <pyversor/types.h>
#include <pyversor/versors.h>

namespace pyversor {

namespace py = pybind11;

namespace ega {

void add_submodule(py::module &m);
void add_vector(py::module &m);
void add_bivector(py::module &m);
void add_trivector(py::module &m);
void add_rotator(py::module &m);
void add_multivector(py::module &m);
void add_generate(py::module &m);

} // namespace ega

namespace cga {

void add_submodule(py::module &m);
// General multivectors
void add_vector(py::module &m);
void add_bivector(py::module &m);
void add_trivector(py::module &m);
void add_quadvector(py::module &m);
void add_pseudoscalar(py::module &m);
void add_origin(py::module &m);
void add_infinity(py::module &m);
void add_multivector(py::module &m);
// Blades
// Rounds
void add_round(py::module &m);

// Flats
void add_dual_line(py::module &m);
void add_line(py::module &m);
void add_dual_plane(py::module &m);
void add_plane(py::module &m);
void add_flat_point(py::module &m);
// Directions
void add_direction_vector(py::module &m);
void add_direction_bivector(py::module &m);
void add_direction_trivector(py::module &m);
void add_direction_quadvector(py::module &m);
// Tangents

// Versors
void add_motor(py::module &m);

void add_flat(py::module &m);
void add_construct(py::module &m);
void add_generate(py::module &m);
void add_operate(py::module &m);

} // namespace cga

} // namespace pyversor