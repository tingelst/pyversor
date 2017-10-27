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

#include <versor/detail/generic_op.h>
#include <versor/space/cga3D_types.h>

namespace vsr {
namespace cga {

//   3D operations on @ref round types (Points, Point Pairs, Circles, Spheres).
//   3D CGA Template Specializations of ND functions found in vsr::nga::Round
//   Note: the ND functions are inlined and can be used instead, but using these
//   will speed up compile times since they are precompiled into libvsr.a
struct Round {
  // Null Point from a vec
  static Point null(const Vec &v);

  // Null Point from a Point
  static Point null(const Point &v);

  // Or Null Point from Coordinates (x,y,z,...)
  static Point null(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z);

  // Null Point from Coordinates
  static Point point(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z);

  // Dual Sphere from Coordinate Center. Note that radius is first argument
  static DualSphere dualSphere(VSR_PRECISION r, VSR_PRECISION x,
                               VSR_PRECISION y, VSR_PRECISION z);

  // Dual Sphere from Coordinate Center (shorthand)
  static DualSphere dls(VSR_PRECISION r, VSR_PRECISION x, VSR_PRECISION y,
                        VSR_PRECISION z) {
    return dualSphere(r, x, y, z);
  }

  // Dual Sphere from Element FIRST and Radius
  static DualSphere dls(const Vec &v, VSR_PRECISION r = 1.0);

  // Dual Sphere from Element FIRST and Radius
  static DualSphere sphere(const Point &v, VSR_PRECISION r = 1.0);

  // Dual Sphere from Point and Radius (faster)
  static DualSphere dls(const Point &p, VSR_PRECISION r = 1.0);

  // Simple Center of A Round (not normalized -- use loc or location method
  // instead)
  static Point center(const DualSphere &s);

  // Simple Center of A Pair (not normalized -- use loc or location method
  // instead)
  static Point center(const Pair &s);

  // Simple Center of A Circle (not normalized -- use loc or location method
  // instead)
  static Point center(const Circle &s);

  //   Simple Center of A Sphere(not normalized-- use loc or location method
  //   instead)
  static Point center(const Sphere &s);

  // Simple Center of a round Element (shorthand)
  template <class A>
  static Point cen(const A &s) {
    return center(s);
  }

  // Location (normalized) of A Round Element (normalized) (Shorthand)
  template <class A>
  static Point location(const A &s) {
    return null(cen(s));
  }

  // Location (normalizd) of a @ref round Element (shorthand)
  template <class A>
  static Point loc(const A &s) {
    return location(s);
  }

  // Squared Size of a DualSphere (result could be negative)
  static VSR_PRECISION size(const DualSphere &s, bool bDual = true);

  // Squared Size of a Point Pair (result could be negative)
  static VSR_PRECISION size(const Pair &s, bool bDual = true);

  // Squared Size of a Circle (result could be negative)
  static VSR_PRECISION size(const Circle &s, bool bDual = false);

  // Squared Size of a Sphere (result could be negative)
  static VSR_PRECISION size(const Sphere &s, bool bDual = false);

  // Squared Size of Normalized Dual Sphere (faster than general case)
  static VSR_PRECISION dsize(const Point &dls);

  // Radius of DualSphere
  static VSR_PRECISION radius(const DualSphere &s);

  // Radius of Pair
  static VSR_PRECISION radius(const Pair &s);

  // Radius of Circle
  static VSR_PRECISION radius(const Circle &s);

  // Radius of Sphere
  static VSR_PRECISION radius(const Sphere &s);

  template <class T>
  static VSR_PRECISION rad(const T &t) {
    return radius(t);
  }

  // Curvature of Round
  template <class A>
  static VSR_PRECISION curvature(const A &s) {
    VSR_PRECISION r = rad(s);
    return (r == 0) ? 10000 : 1.0 / rad(s);
  }

  // Curvature of Round
  template <class T>
  static VSR_PRECISION cur(const T &t) {
    return curvature(t);
  }

  // Squared distance between two points
  static VSR_PRECISION squaredDistance(const Point &a, const Point b);

  // Squared distance between two points
  static VSR_PRECISION sqd(const Point &a, const Point b) {
    return squaredDistance(a, b);
  }

  // Distance between points a and b
  static VSR_PRECISION distance(const Point &a, const Point b);

  // Distance between points a and b (shorthand)
  static VSR_PRECISION dist(const Point &a, const Point &b) {
    return distance(a, b);
  }

  // Split Points from Point Pair
  static std::vector<Point> split(const Pair &pp);

  // Split Points from Point Pair and normalize
  static std::vector<Point> splitLocation(const Pair &pp);

  // Split a point pair and return one
  static Point split(const Pair &pp, bool bFirst);

  // Split A Circle into its dual point pair poles
  static std::vector<Point> split(const Circle &nc) { return split(nc.dual()); }

  // Split A Circle into its dual point pair poles and normalize
  static std::vector<Point> splitLocation(const Circle &nc) { return splitLocation(nc.dual()); }

  // Direction of a Pair
  static DirectionVector direction(const Pair &p);

  // Direction of a Circle
  static DirectionBivector direction(const Circle &c);

  // Direction of a Sphere
  static DirectionTrivector direction(const Sphere &c);

  // Direction of Round Element (shorthand)
  template <class A>
  static auto dir(const A &s) -> decltype(direction(s)) {
    return direction(s);
  }

  static DualSphere normalize(const DualSphere &x) {
    VSR_PRECISION wt = direction(x.undual())[0];
    return x / wt;
  };

  static Sphere normalize(const Sphere &x) {
    VSR_PRECISION wt = direction(x)[0];
    return x / wt;
  };

  static Pair normalize(const Pair &x) {
    VSR_PRECISION wt = (-direction(x).copy<Vec>()).norm();
    return x / wt;
  };

  static Circle normalize(const Circle &x) {
    VSR_PRECISION wt = direction(x).copy<Biv>().rnorm();
    return x / wt;
  };

  static Pair renormalize(const Pair &x) {
    auto tmp = (-direction(x)).copy<Vec>().unit().copy<Tnv>();
    return Pair(tmp).translate(Round::location(x));
  };

  static Circle renormalize(const Circle &x) {
    auto tmp = (direction(x)).copy<Biv>().runit().copy<Tnb>();
    return Circle(tmp).translate(Round::location(x));
  };

  //    static DualSphere renormalize( const DualSphere& x ){
  //      auto tmp = direction(x.undual())[0];
  //      return DualSphere(x/tmp).translate( Round::location(x) );
  //    };
  //
  //    static Circle renormalize( const Circle& x ){
  //      auto tmp = (direction(x)).copy<Biv>().runit().copy<Tnb>();
  //      return Circle(tmp).translate( Round::location(x) );
  //    };

  // Carrier Flat of Pair
  static Line carrier(const Pair &p);

  // Carrier Flat of Circle
  static Plane carrier(const Circle &c);

  // Carrier Flat of Direct? Round Element (Shorthand)
  template <class A>
  static auto car(const A &s) -> decltype(carrier(s)) {
    return carrier(s);
  }

  // Dual Surround of a Direct or Dual Pair
  static DualSphere surround(const Pair &s);

  // Dual Surround of a Direct or Dual Circle
  static DualSphere surround(const Circle &s);

  // Dual Surround of a Direct or Dual Round Element (Shorthand)
  template <class A>
  static DualSphere sur(const A &s) {
    return surround(s);
  }

  // Pair From DualSphere and @ref euclidean subspace Bivector
  // Note: Result will be imaginary if input DualSphere is real . .
  static Pair produce(const DualSphere &dls, const Vec &v);

  // Circle From DualSphere and @ref euclidean subspace Bivector
  // Note: Result will be imaginary if input DualSphere is real . .
  static Circle produce(const DualSphere &dls, const Biv &b);

  //    /*
  //      Creates a real / imaginary round from an imaginary / real round
  //     */
  //     template<class A>
  //     auto
  //     real(const A& s) RETURNS (
  //         produce(
  //                Round::dls( Round::loc( s ), -Round::rad( Round::sur( s ) )
  //                ),
  //                typename A::space::origin(-1) <= Round::dir( s )
  //              )
  //     )
  //
  //
  //    /*
  //      Creates an imaginary round from an real round
  //     */
  //     template<class A>
  //     auto
  //     imag(const A& s) RETURNS (
  //         produce(
  //                Round::dls( Round::loc( s ), Round::rad( Round::sur( s ) )
  //                ),
  //                typename A::space::origin(-1) <= Round::dir( s )
  //              )
  //     )

  // Dual Round from Center and Point on Surface
  static DualSphere at(const Point &c, const Point &p);

  // Direct Point From Dual Sphere and Euclidean Carrier Flat
  static Point point(const DualSphere &dls, const Vec &flat);

  // Euclidean Vector of Circle at theta
  static Vec vec(const Circle &c, VSR_PRECISION theta = 0);

  // Point Pair on Direct Circle at angle t
  static Pair pair(const Circle &c, VSR_PRECISION t);

  // Point on Circle at angle t
  static Point point(const Circle &c, VSR_PRECISION t);

  // Theta in radians of point on circle relative to origin
  static VSR_PRECISION theta(const Circle &circle, const Point &point);
};

// 3D operations on @ref flat types
struct Flat {
  // Direction of Line
  static DirectionVector direction(const Line &f);

  // Direction of Plane
  static DirectionBivector direction(const Plane &f);

  // Direction shorthand
  template <class A>
  static auto dir(const A &s) {
    return direction(s);
  }

  // Location of DualLine closest to Point p
  static Point location(const DualLine &f, const Point &p, bool dual = true);

  // Location of Line closest to Point p
  static Point location(const Line &f, const Point &p, bool dual = false);

  // Location of DualPlane closest to Point p
  static Point location(const DualPlane &f, const Point &p, bool dual = true);

  // Location of Plane closest to Point p
  static Point location(const Plane &f, const Point &p, bool dual = false);

  // Location of flat (shorthand)
  template <class A>
  static Point loc(const A &a, const Point &p, bool dual) {
    return location(a, p);
  }

  // Weight of DualLine
  static double wt(const DualLine &f, bool bDual = true);

  // Dual Plane from Point and Direction
  static DualPlane plane(const Point &pnt, const DirectionVector &drv);

  // Direct Line at origin with coordinate v ...
  static Line line(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z);

  // Direct hyperbolic d-Line at origin with coordinate v ...
  static Circle dline(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z);
};

// 3D operations on tangent types
struct Tangent {
  // Tangent Element of A Circle at Point p
  static Pair at(const Circle &r, const Point &p);

  // Tangent Element of A Sphere at Point p
  static Circle at(const Sphere &r, const Point &p);

  // Weight of TangentVector
  static VSR_PRECISION wt(const TangentVector &s);

  // Weight of TangentBiVector
  static VSR_PRECISION wt(const TangentBivector &s);

  // Weight of TangentTrivector
  static VSR_PRECISION wt(const TangentTrivector &s);
};

}  // namespace cga

}  // namespace vsr