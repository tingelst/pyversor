#include <pyversor/round.h>

namespace pyversor {

namespace cga {

template <typename A, typename B, typename C, typename module_t>
auto def_outer(module_t &m) {
  m.def("__xor__", [](const A &lhs, const B &rhs) { return C(lhs ^ rhs); });
  m.def("outer", [](const A &lhs, const B &rhs) { return C(lhs ^ rhs); });
}

template <typename A, typename B, typename module_t>
auto def_outer(module_t &m) {
  m.def("__xor__", [](const A &lhs, const B &rhs) { return lhs ^ rhs; });
  m.def("outer", [](const A &lhs, const B &rhs) { return lhs ^ rhs; });
}

template <typename A, typename B, typename module_t>
auto def_inner(module_t &m) {
  m.def("__le__", [](const A &lhs, const B &rhs) { return lhs <= rhs; });
  m.def("inner", [](const A &lhs, const B &rhs) { return lhs <= rhs; });
}

void add_round(py::module &m) {
  using vsr::cga::Round;
  auto t = m.def_submodule("round");
  round::add_null<ega::vector_t>(t);
  round::add_null<cga::vector_t>(t);
  round::add_distance<vector_t>(m);
  round::add_squared_distance<vector_t>(m);
  round::add_radius_center_location<dual_sphere_t>(t);
  round::add_radius_center_location<sphere_t>(t);
  round::add_radius_center_location<point_pair_t>(t);
  round::add_radius_center_location<circle_t>(t);

  round::add_normalize<dual_sphere_t>(t);
  round::add_normalize<sphere_t>(t);
  round::add_normalize<point_pair_t>(t);
  round::add_normalize<circle_t>(t);

  round::add_size<dual_sphere_t, true>(t);
  round::add_size<sphere_t, false>(t);
  round::add_size<point_pair_t, true>(t);
  round::add_size<circle_t, false>(t);

  round::add_carrier<point_pair_t>(t);
  round::add_carrier<circle_t>(t);
  round::add_surround<point_pair_t>(t);
  round::add_surround<circle_t>(t);
  round::add_renormalize<point_pair_t>(t);
  round::add_renormalize<circle_t>(t);
  round::add_direction<point_pair_t>(t);
  round::add_direction<circle_t>(t);
  round::add_split<point_pair_t>(t);
  round::add_split<circle_t>(t);

  round::add_produce<vector_t>(t);

  auto vec = add_conformal_multivector<vector_t>(t, "Vector");

  auto pnt = add_conformal_multivector<point_t>(t, "Point");
  pnt.def(py::init<ega::vector_t>());
  pnt.def(py::init<cga::vector_t>());
  pnt.def(py::init<double, double, double>());
  def_outer<point_t, point_t, point_pair_t>(pnt);
  def_outer<point_t, point_pair_t, circle_t>(pnt);
  def_outer<point_t, circle_t, sphere_t>(pnt);
  def_outer<point_t, infinity_t, flat_point_t>(pnt);

  py::implicitly_convertible<vector_t, point_t>();

  auto dls = add_conformal_multivector<dual_sphere_t>(t, "DualSphere");
  dls.def(py::init<dual_sphere_t>(), "Construct a dual sphere");
  dls.def(py::init<point_t, double>(),
          "Construct a dual sphere from a conformal center point and radius");
  dls.def(py::init<double, double, double, double>());

  py::implicitly_convertible<dual_sphere_t, vector_t>();

  auto biv = py::class_<bivector_t>(t, "Bivector");
  auto pp = py::class_<point_pair_t, bivector_t>(t, "PointPair");
  pp.def(py::init<point_t, point_t>());
  def_outer<point_pair_t, point_t, circle_t>(pp);
  def_outer<point_pair_t, point_pair_t, sphere_t>(pp);
  def_outer<point_pair_t, flat_point_t, plane_t>(pp);
  def_outer<point_pair_t, infinity_t, line_t>(pp);

  py::implicitly_convertible<bivector_t, point_pair_t>();

  auto tri = py::class_<trivector_t>(t, "Trivector");
  auto cir = py::class_<circle_t, trivector_t>(t, "Circle");
  cir.def(py::init<point_t, point_t, point_t>());
  def_outer<circle_t, point_t, sphere_t>(cir);
  def_outer<circle_t, infinity_t, plane_t>(cir);

  py::implicitly_convertible<trivector_t, circle_t>();

  auto sph = py::class_<sphere_t>(t, "Sphere");
  sph.def(py::init<sphere_t>(), "Construct a direct sphere");
  sph.def(py::init<point_t, double>(),
          "Construct a direct sphere from a conformal center point and radius");
  sph.def(py::init<double, double, double, double>());
  sph.def(py::init<point_t, point_t, point_t, point_t>());

  // auto sph = py::class_<sphere_t>(t, "Sphere", py::module_local());
  // sph.def(py::init([](const point_t &p, double r) {
  //   return vsr::cga::Construct::sphere(p, r);
  // }));
  // auto pp = py::class_<point_pair_t>(t, "PointPair", py::module_local());
  // auto c = py::class_<circle_t>(t, "Circle", py::module_local());
}

} // namespace cga

} // namespace pyversor
