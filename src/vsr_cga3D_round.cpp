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

#include <versor/space/cga3D_round.h>

namespace vsr {
namespace cga {

// Null Point from a vec
Point Round::null(const Vec &v) { return vsr::nga::Round::null(v); }

// Null Point from a Point
Point Round::null(const Point &p) { return vsr::nga::Round::null(p); }

// Or Null Point from Coordinates (x,y,z,...)
Point Round::null(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z) {
  return vsr::nga::Round::null(x, y, z);
}

// Null Point from Coordinates
Point Round::point(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z) {
  return vsr::nga::Round::null(x, y, z);
}

// Dual Sphere from Coordinate Center
DualSphere Round::dualSphere(VSR_PRECISION r, VSR_PRECISION x, VSR_PRECISION y,
                             VSR_PRECISION z) {
  return vsr::nga::Round::dls(r, x, y, z);
}

// Dual Sphere from Element FIRST and Radius
DualSphere Round::dls(const Vec &v, VSR_PRECISION r) {
  return vsr::nga::Round::dls(v, r);
}

// Dual Sphere from Element FIRST and Radius
DualSphere Round::sphere(const Point &v, VSR_PRECISION r) {
  return vsr::nga::Round::sphere(v, r);
}

// Dual Sphere from Point and Radius (faster)
DualSphere Round::dls(const Point &p, VSR_PRECISION r) {
  return vsr::nga::Round::dls(p, r);
}

// Simple Center of A DualSphere (not normalized -- use loc or location method)
Point Round::center(const DualSphere &s) { return vsr::nga::Round::center(s); }

// Simple Center of A Pair (not normalized -- use loc or location method)
Point Round::center(const Pair &s) { return vsr::nga::Round::center(s); }

// Simple Center of A Circle (not normalized -- use loc or location method)
Point Round::center(const Circle &s) { return vsr::nga::Round::center(s); }
// Simple Center of A Sphere (not normalized -- use loc or location method)
Point Round::center(const Sphere &s) { return vsr::nga::Round::center(s); }

// Squared Size of a DualSphere (result could be negative)
VSR_PRECISION Round::size(const DualSphere &s, bool bDual) {
  return vsr::nga::Round::size(s, true);
}

// Squared Size of a Point Pair (result could be negative)
VSR_PRECISION Round::size(const Pair &s, bool bDual) {
  return vsr::nga::Round::size(s, bDual);
}

// Squared Size of a Circle (result could be negative)
VSR_PRECISION Round::size(const Circle &s, bool bDual) {
  return vsr::nga::Round::size(s, bDual);
}

// Squared Size of a Sphere (result could be negative)
VSR_PRECISION Round::size(const Sphere &s, bool bDual) {
  return vsr::nga::Round::size(s, false);
}

// Radius of DualSphere
VSR_PRECISION Round::radius(const DualSphere &s) {
  return vsr::nga::Round::radius(s);
}

// Radius of Pair
VSR_PRECISION Round::radius(const Pair &s) {
  return vsr::nga::Round::radius(s);
}

// Radius of Circle
VSR_PRECISION Round::radius(const Circle &s) {
  return vsr::nga::Round::radius(s);
}

// Radius ofSphere
VSR_PRECISION Round::radius(const Sphere &s) {
  return vsr::nga::Round::radius(s);
}

// Squared Size of Normalized Dual Sphere (faster than general case)
VSR_PRECISION Round::dsize(const Point &dls) {
  return vsr::nga::Round::dsize(dls);
}

// Squared distance between two points
VSR_PRECISION Round::squaredDistance(const Point &a, const Point b) {
  return vsr::nga::Round::squaredDistance(a, b);
}

// Distance between points a and b
VSR_PRECISION Round::distance(const Point &a, const Point b) {
  return vsr::nga::Round::distance(a, b);
}

// Split Points from Point Pair
std::vector<Point> Round::split(const Pair &pp) {
  return vsr::nga::Round::split(pp);
}

// Split Points from Point Pair and normalize
std::vector<Point> Round::splitLocation(const Pair &pp) {
  return vsr::nga::Round::splitLocation(pp);
}

//
Point Round::split(const Pair &pp, bool bSecond) {
  return vsr::nga::Round::split(pp, bSecond);
}

// Direction of a Pair
DirectionVector Round::direction(const Pair &p) {
  return vsr::nga::Round::direction(p);
}

// Direction of a Circle
DirectionBivector Round::direction(const Circle &c) {
  return vsr::nga::Round::direction(c);
}

// Direction of a Sphere
DirectionTrivector Round::direction(const Sphere &c) {
  return vsr::nga::Round::direction(c);
}

// Carrier Flat of Pair
Line Round::carrier(const Pair &p) { return vsr::nga::Round::carrier(p); }

// Carrier Flat of Circle
Plane Round::carrier(const Circle &c) { return vsr::nga::Round::carrier(c); }

// Dual Surround of a Direct or Dual Pair
DualSphere Round::surround(const Pair &s) {
  return vsr::nga::Round::surround(s);
}

// Dual Surround of a Direct or Dual Circle
DualSphere Round::surround(const Circle &s) {
  return vsr::nga::Round::surround(s);
}

// Direct Round From Dual Sphere and Euclidean Bivector
// Note: round will be imaginary if dual sphere is real
Pair Round::produce(const DualSphere &dls, const Vec &v) {
  return vsr::nga::Round::produce(dls, v);
}

// Direct Round From Dual Sphere and Euclidean Bivector
// Note: round will be imaginary if dual sphere is real . .
Circle Round::produce(const DualSphere &dls, const Biv &v) {
  return vsr::nga::Round::produce(dls, v);
}

// // Creates a real / imaginary round from an imaginary / real round
// template <class A>
// auto real(const A &s) {
//   return (produce(Round::dls(Round::loc(s), -Round::rad(Round::sur(s))),
//                   typename A::space::origin(-1) <= Round::dir(s)));
// }

// // Creates an imaginary round from an real round
// template <class A>
// auto imag(const A &s) {
//   return (produce(Round::dls(Round::loc(s), Round::rad(Round::sur(s))),
//                   typename A::space::origin(-1) <= Round::dir(s)));
// }

// Dual Round from Center and Point on Surface
DualSphere Round::at(const DualSphere &c, const DualSphere &p) {
  return vsr::nga::Round::at(c, p);
}

// Direct Point From Dual Sphere and Euclidean Carrier Flat
Point Round::point(const DualSphere &dls, const Vec &flat) {
  return vsr::nga::Round::pnt(dls, flat);
}

// Euclidean Vector of Circle at theta
Vec Round::vec(const Circle &c, VSR_PRECISION theta) {
  return vsr::nga::Round::vec(c, theta);
}

// Point Pair on Direct Circle at angle t
Pair Round::pair(const Circle &c, VSR_PRECISION t) {
  return vsr::nga::Round::par_cir(c, t);
}

// Point on Circle at angle t
Point Round::point(const Circle &c, VSR_PRECISION t) {
  return vsr::nga::Round::pnt_cir(c, t);
}

// Theta in radians of point p relative to circle circle. @todo, does not
// consider quadrant!
VSR_PRECISION Round::theta(const Circle &circle, const Point &point) {
  /// Tangent Element on circle at point
  auto t = Tangent::at(circle, point);
  /// Direction of point relative to circle center
  auto dir = Vec(Round::location(t) - Round::location(circle)).unit();
  /// Spin e1 by rotor which takes e3 to normal
  auto tx = Vec::x.spin(
      vsr::nga::Gen::ratio(Vec::z, Vec(Round::carrier(circle).dual().unit())));
  /// Theta that takes tx to to dir
  auto phi = atan2((dir ^ tx).rnorm(), (dir <= tx)[0]);
  return phi;
}

// Direction of Line
DirectionVector Flat::direction(const Line &f) {
  return nga::Flat::direction(f);
}

// Direction of Plane
DirectionBivector Flat::direction(const Plane &f) {
  return nga::Flat::direction(f);
}

// Location of DualLine closest to Point p
Point Flat::location(const DualLine &f, const Point &p, bool dual) {
  return nga::Flat::location(f, p, dual);
}

// Location of Line closest to Point p
Point Flat::location(const Line &f, const Point &p, bool dual) {
  return nga::Flat::location(f, p, dual);
}

// Location of DualPlane closest to Point p
Point Flat::location(const DualPlane &f, const Point &p, bool dual) {
  return nga::Flat::location(f, p, dual);
}

// Location of Plane closest to Point p
Point Flat::location(const Plane &f, const Point &p, bool dual) {
  return nga::Flat::location(f, p, dual);
}

// Weight of DualLine
VSR_PRECISION Flat::wt(const DualLine &f, bool bDual) {
  return nga::Flat::wt(f, bDual);
}

// Dual Plane from Point and Direction
DualPlane Flat::plane(const Point &pnt, const DirectionVector &drv) {
  return nga::Flat::dlp(pnt, drv);
}

// Direct Line at origin with coordinate v ...
Line Flat::line(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z) {
  return nga::Flat::line(x, y, z);
}

/*! Direct hyperbolic d-Line at origin with coordinate v ... */
Circle Flat::dline(VSR_PRECISION x, VSR_PRECISION y, VSR_PRECISION z) {
  return nga::Flat::dline(x, y, z);
}

// Tangent Element of A Circle at Point p
Pair Tangent::at(const Circle &r, const Point &p) {
  return nga::Tangent::at(r, p);
}

// Tangent Element of A Sphere at Point p
Circle Tangent::at(const Sphere &r, const Point &p) {
  return nga::Tangent::at(r, p);
}

// Weight of TangentVector
VSR_PRECISION Tangent::wt(const TangentVector &s) {
  return nga::Tangent::wt(s);
}

// Weight of TangentBiVector
VSR_PRECISION Tangent::wt(const TangentBivector &s) {
  return nga::Tangent::wt(s);
}

// Weight of TangentTrivector
VSR_PRECISION Tangent::wt(const TangentTrivector &s) {
  return nga::Tangent::wt(s);
}

}  // namespace cga

}  // namespace vsr
