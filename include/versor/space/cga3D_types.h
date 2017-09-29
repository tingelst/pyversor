// Versor Geometric Algebra Library
// Copyright (c) 2017 Lars Tingelstad
// Copyright (c) 2010 Pablo Colapinto
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// The views and conclusions contained in the software and documentation are
// those of the authors and should not be interpreted as representing official
// policies, either expressed or implied, of the FreeBSD Project.

#pragma once

#include <versor/detail/multivector.h>

namespace vsr {

namespace cga {

using Sca = NSca<5>; // Scalar
using Vec = NVec<5>; // Vector
using Biv = NBiv<5>; // Bivector
using Rot = NRot<5>; // Rotor
using Tri = NTri<5>; // Trivector
using Ori = NOri<5>; // Origin
using Inf = NInf<5>; // Infinity
using Mnk = NMnk<5>; // Minkowski
using Pss = NPss<5>; // Pseudoscalar
using Pnt = NPnt<5>; // Point
using Par = NPar<5>; // Pair
using Cir = NCir<5>; // Circle
using Sph = NSph<5>; // Sphere
using Dls = NDls<5>; // DualSphere
using Flp = NFlp<5>; // FlatPoint
using Dll = NDll<5>; // DualLine
using Lin = NLin<5>; // Line
using Dlp = NDlp<5>; // DualPlane
using Pln = NPln<5>; // Plane
using Drv = NDrv<5>; // DirectionVector
using Tnv = NTnv<5>; // TangentVector
using Drb = NDrb<5>; // DirectionBivector
using Tnb = NTnb<5>; // TangentBivector
using Drt = NDrt<5>; // DirectionTrivector
using Tnt = NTnt<5>; // TangentTrivector
using Trs = NTrs<5>; // Translator
using Mot = NMot<5>; // Motor
using Trv = NTrv<5>; // Transversor
using Bst = NBst<5>; // Boost
using Con = NCon<5>; // ConformalRotor
using Dil = NDil<5>; // Dilator
using Tsd = NTsd<5>; // TranslatedDilator

typedef Sca Scalar;
typedef Vec Vector;
typedef Biv Bivector;
typedef Tri Trivector;
typedef Rot Rotor;
typedef Ori Origin;
typedef Inf Infinity;
typedef Mnk Minkowski;
typedef Pss Pseudoscalar;
typedef Pnt Point;
typedef Par Pair;
typedef Cir Circle;
typedef Sph Sphere;
typedef Pnt DualSphere;
typedef Drv DirectionVector;
typedef Drb DirectionBivector;
typedef Drt DirectionTrivector;
typedef Tnv TangentVector;
typedef Tnb TangentBivector;
typedef Tnt TangentTrivector;
typedef Dll DualLine;
typedef Lin Line;
typedef Flp FlatPoint;
typedef Pln Plane;
typedef Dlp DualPlane;
typedef Trs Translator;
typedef Mot Motor;
typedef Trv Transversor;
typedef Bst Boost;
typedef Con ConformalRotor;
typedef Dil Dilator;
typedef Tsd TranslatedDilator;
}
}