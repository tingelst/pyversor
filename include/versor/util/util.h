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

namespace vsr {

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef TWOPI
#define TWOPI 6.283185307179586
#endif

#ifndef PIOVERTWO
#define PIOVERTWO 1.570796326794897
#endif

#ifndef PIOVERFOUR
#define PIOVERFOUR 0.785398163397448
#endif

#ifndef THREEPIOVERTWO
#define THREEPIOVERTWO 4.71238898038469
#endif

#ifndef PHI
#define PHI 1.61803
#endif

#ifndef ONEOVERPHI
#define ONEOVERPHI .61803
#endif

#ifndef CHANCE
#define CHANCE 1.13198824
#endif

#ifndef GOLDENANGLE
#define GOLDENANGLE 137.507764
#endif

#ifndef GOLDENRADIAN
#define GOLDENRADIAN 2.399963
#endif

#ifndef SMALLRAD
#define SMALLRAD (PI * 36 / 180)
#endif

#ifndef MEDIUMRAD
#define MEDIUMRAD (PI * 72 / 180)
#endif

#ifndef LARGERAD
#define LARGERAD (PI * 108 / 180)
#endif

#ifndef ROOT2
#define ROOT2 1.41421
#endif

#ifndef ROOT3
#define ROOT3 1.73205
#endif

#ifndef FPERROR
#define FPERROR .000001
#endif

#ifndef ERROR
#define ERROR(x, y) (x <= y && x >= -y)
#endif

#ifndef MAXRADIUS
#define MAXRADIUS 100000
#endif

#ifndef FERROR
#define FERROR(x) (fabs(x) <= FPERROR)
#endif

#ifndef CLAMP
#define CLAMP(val, min, max) val<min ? min : val> max ? max : val
#endif

#ifndef D2R
#define D2R(val) PI *val / 180.0
#endif

#ifndef ZERO
#define ZERO(x) (fabs(x) < FPERROR ? 0 : x)
#endif

struct Math {
  static double sinc(double x);
  static double sinhc(double x);
  static double clamp(double x, double min, double max);
  static double map(double x, double min, double max, double rmin, double rmax);

  static int bitcount(int x);

  template <typename T> inline static bool Range(T v, T low, T high) {
    return (v >= low && v <= high) ? true : false;
  }

  template <typename T> inline static bool Error(T v, T goal, T error) {
    return Range(v, goal - error, goal + error);
  }
};

inline double Math::sinc(double x) {
  if (FERROR(x))
    return 1;
  else
    return sin(x) / (x);
}

inline double Math::sinhc(double x) {
  if (FERROR(x))
    return 1;
  else
    return sinh(x) / x;
}

inline double Math::clamp(double x, double min, double max) {
  return (x < min) ? min : (x > max) ? max : x;
}

inline double Math::map(double x, double min, double max, double rmin,
                        double rmax) {
  double orange = max - min;
  double drange = rmax - rmin;

  double offset = x - min;
  double ratio = offset / orange;

  double doffset = ratio * drange;

  return rmin + doffset;
}

inline int Math::bitcount(int x) {
  int n = 0;
  do {
    if (x & 1)
      n += 1;
    x = x >> 1;
  } while (x);
  return n;
}
}
