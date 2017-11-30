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

#include <pyversor/c3d/types.h>
#include <pyversor/e41/e41.h>
#include <pyversor/pyversor.h>

namespace pyversor {

namespace e41 {

using e41_t = vsr::algebra<vsr::metric<4, 1, false>, double>;

using multivector_t =
    vsr::Multivector<e41_t, vsr::Basis<0, 1, 2, 4, 8, 16, 3, 5, 6, 9, 10, 12,
                                       17, 18, 20, 24, 7, 11, 13, 14, 19, 21,
                                       22, 25, 26, 28, 15, 23, 27, 29, 30, 31>>;

auto exp(const e41::multivector_t &b) {
  auto bb = b * b;
  auto ans = (bb * 0.5) + b + 1.0;
  std::array<double, 18> inverse_factorials{
      0.16666666666666666,    0.041666666666666664,   0.008333333333333333,
      0.001388888888888889,   0.0001984126984126984,  2.48015873015873e-05,
      2.7557319223985893e-06, 2.755731922398589e-07,  2.505210838544172e-08,
      2.08767569878681e-09,   1.6059043836821613e-10, 1.1470745597729725e-11,
      7.647163731819816e-13,  4.779477332387385e-14,  2.8114572543455206e-15,
      1.5619206968586225e-16, 8.22063524662433e-18,   4.110317623312165e-19};
  for (auto invfac : inverse_factorials) {
    bb *= b;
    ans += bb * invfac;
  }
  return ans;
}

void def_submodule(py::module &m) {
  auto e41_m = m.def_submodule("e41");
  e41_m.def("exp", &exp);
  auto mv = def_multivector<e41::multivector_t>(e41_m, "Multivector");
  mv.def(py::init<double, double, double, double, double, double, double,
                  double, double, double, double, double, double, double,
                  double, double, double, double, double, double, double,
                  double, double, double, double, double, double, double,
                  double, double, double, double>());
  mv.def(py::init<c3d::multivector_t>());
  def_scalar_addition<e41::multivector_t>(mv);
  def_geometric_product<e41::multivector_t, e41::multivector_t>(mv);
  def_outer_product<e41::multivector_t, e41::multivector_t>(mv);
  def_inner_product<e41::multivector_t, e41::multivector_t>(mv);
  // Division
  mv.def("__truediv__",
         [](const e41::multivector_t &lhs, const e41::multivector_t &rhs) {
           return lhs / rhs;
         },
         py::is_operator());
}

} // namespace e41

} // namespace pyversor
