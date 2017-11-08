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

#include <pyversor/c2d/c2d.h>
#include <pyversor/pyversor.h>

namespace pyversor {

namespace c2d {

using c2d_t = vsr::algebra<vsr::metric<3, 1, true>, double>;

using multivector_t = vsr::Multivector<
    c2d_t, vsr::Basis<0, 1, 2, 4, 8, 3, 5, 6, 9, 10, 12, 7, 11, 13, 14, 15>>;

void def_submodule(py::module &m) {
  auto c2d = m.def_submodule("c2d");
  auto mv = def_multivector<c2d::multivector_t>(c2d, "Multivector");
  mv.def(py::init<double, double, double, double, double, double, double,
                  double, double, double, double, double, double, double,
                  double, double>());
  def_geometric_product<c2d::multivector_t, c2d::multivector_t>(mv);
  def_outer_product<c2d::multivector_t, c2d::multivector_t>(mv);
  def_inner_product<c2d::multivector_t, c2d::multivector_t>(mv);
}

}  // namespace c2d

}  // namespace pyversor
