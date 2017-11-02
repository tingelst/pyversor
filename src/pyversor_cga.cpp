#include <pyversor/pyversor.h>

namespace pyversor {

namespace cga {

void add_submodule(py::module &m) {
  auto cga = m.def_submodule("cga");
  // add_vector(cga);
  // add_bivector(cga);
  // add_trivector(cga);
  // add_quadvector(cga);
  // add_multivector(cga);
  // add_motor(cga);
  // add_dual_line(cga);
  // add_line(cga);
  add_flat_point(cga);
  // add_dual_plane(cga);
  add_plane(cga);
  // add_origin(cga);
  add_infinity(cga);
  // add_direction_vector(cga);
  // add_direction_bivector(cga);
  // add_direction_trivector(cga);
  add_round(cga);
  add_flat(cga);
  add_construct(cga);
  add_generate(cga);
  add_operate(cga);
}

void add_vector(py::module &m) {
  // auto t = add_conformal_multivector<vector_t>(m, "Vector");
  // t.def(py::init<double, double, double, double, double>());
  // round::add_null<vector_t>(t);
  // round::add_radius_center_location<vector_t>(t);
  // round::add_produce<vector_t>(t);
  // round::add_normalize<vector_t>(t);
  // round::add_distance<vector_t>(t);
  // round::add_squared_distance<vector_t>(t);
  // round::add_size<vector_t, true>(t);
  // outer_product<vector_t>::add<bivector_t, trivector_t, quadvector_t,
  // origin_t,
  //                              infinity_t>(t);
}

void add_bivector(py::module &m) {
  auto t = add_conformal_multivector<bivector_t>(m, "Bivector");
  t.def(py::init<double, double, double, double, double, double, double, double,
                 double, double>());
  // round::add_radius_center_location<bivector_t>(t);
  // round::add_carrier<bivector_t>(t);
  // round::add_surround<bivector_t>(t);
  // round::add_normalize<bivector_t>(t);
  // round::add_renormalize<bivector_t>(t);
  // round::add_direction<bivector_t>(t);
  // round::add_split<bivector_t>(t);
  // round::add_size<bivector_t, true>(t);
}

void add_trivector(py::module &m) {
  auto t = add_conformal_multivector<trivector_t>(m, "Trivector");
  t.def(py::init<double, double, double, double, double, double, double, double,
                 double, double>());
  // round::add_radius_center_location<trivector_t>(t);
  // round::add_carrier<trivector_t>(t);
  // round::add_surround<trivector_t>(t);
  // round::add_normalize<trivector_t>(t);
  // round::add_renormalize<trivector_t>(t);
  // round::add_direction<trivector_t>(t);
  // round::add_split<trivector_t>(t);
  // round::add_size<trivector_t, false>(t);
}

void add_quadvector(py::module &m) {
  auto t = add_conformal_multivector<quadvector_t>(m, "Quadvector");
  t.def(py::init<double, double, double, double, double>());
  // round::add_radius_center_location<quadvector_t>(t);
  // round::add_normalize<quadvector_t>(t);
  // round::add_size<quadvector_t, false>(t);
}

void add_origin(py::module &m) {
  auto t = py::class_<origin_t>(m, "Origin");
  t.def(py::init<double>());
}

void add_infinity(py::module &m) {
  auto t = py::class_<infinity_t>(m, "Infinity");
  t.def(py::init<double>());
}

void add_motor(py::module &m) {
  add_conformal_multivector<motor_t>(m, "Motor")
      .def(py::init<double, double, double, double, double, double, double,
                    double>())
      .def("rotator", [](const motor_t &arg) { return ega::rotator_t(arg); })
      .def("normalize", [](const motor_t &arg) {
        auto norm = arg.norm();
        auto b = arg * ~arg;
        auto s0 = b[0];
        auto s4 = b[7];
        auto s_inv =
            scalar_t{(1.0) / norm} *
            (scalar_t{(1.0)} + direction_trivector_t{-(s4 / (2.0 * s0))});
        return arg * s_inv;
      });
}

struct flat {
  template <typename flat_t, bool dual, typename module_t = py::module>
  static void add_location(module_t &m) {
    using vsr::cga::Flat;
    using vsr::cga::Round;
    m.def("location", [](const flat_t &a) {
      return Flat::location(a, Round::null(ega::vector_t{0.0, 0.0, 0.0}), dual);
    });
    m.def("location", [](const flat_t &a, const point_t &b) {
      return Flat::location(a, Round::null(b), dual);
    });
  }

  template <typename flat_t, typename module_t = py::module>
  static void add_direction(module_t &m) {
    using vsr::cga::Flat;
    m.def("direction", [](const flat_t &a) { return Flat::direction(a); });
  }
};

void add_dual_line(py::module &m) {
  auto t = add_conformal_multivector<dual_line_t>(m, "DualLine");
  t.def(py::init<double, double, double, double, double, double>());
  t.def("__add__",
        [](const dual_line_t &a, double b) { return motor_t(a + b); });
  t.def("__radd__",
        [](const dual_line_t &a, double b) { return motor_t(a + b); });
  flat::add_location<dual_line_t, true>(t);
}

void add_line(py::module &m) {
  auto t = add_conformal_multivector<line_t>(m, "Line");
  t.def(py::init<double, double, double, double, double, double>());
  flat::add_location<line_t, false>(t);
  flat::add_direction<line_t>(t);
}

void add_flat_point(py::module &m) {
  auto t = add_conformal_multivector<flat_point_t>(m, "FlatPoint");
  t.def(py::init<double, double, double, double>());
}

void add_dual_plane(py::module &m) {
  auto t = add_conformal_multivector<dual_plane_t>(m, "DualPlane");
  t.def(py::init<double, double, double, double>());
  flat::add_location<dual_plane_t, true>(t);
}

void add_plane(py::module &m) {
  auto t = add_conformal_multivector<plane_t>(m, "Plane");
  t.def(py::init<double, double, double, double>());
  flat::add_location<plane_t, false>(t);
  flat::add_direction<plane_t>(t);
}

// Seems like we need to handle directions differently due to compilation errors
void add_direction_vector(py::module &m) {
  py::class_<direction_vector_t>(m, "DirectionVector")
      .def(py::init<double, double, double>());
  // add_conformal_multivector<direction_vector_t>(m, "DirectionVector")
  //     .def(py::init<double, double, double>());
}

void add_direction_bivector(py::module &m) {
  py::class_<direction_bivector_t>(m, "DirectionBivector")
      .def(py::init<double, double, double>());
  // add_conformal_multivector<direction_bivector_t>(m, "DirectionBivector")
  //     .def(py::init<double, double, double>());
}

void add_direction_trivector(py::module &m) {
  py::class_<direction_trivector_t>(m, "DirectionTrivector")
      .def(py::init<double>());
  // add_conformal_multivector<direction_trivector_t>(m, "DirectionTrivector")
  //     .def(py::init<double>());
}

void add_multivector(py::module &m) {
  add_conformal_multivector<multivector_t>(m, "Multivector")
      .def(py::init<>())
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double>());
}

void add_flat(py::module &m) {
  auto t = m.def_submodule("flat");
  flat::add_location<dual_plane_t, true>(t);
  flat::add_location<plane_t, false>(t);
  flat::add_location<dual_line_t, true>(t);
  flat::add_location<line_t, false>(t);
  flat::add_direction<plane_t>(t);
  flat::add_direction<line_t>(t);
}

void add_construct(py::module &m) {
  using vsr::cga::Construct;
  auto construct = m.def_submodule("construct");
  construct.def("sphere", [](const cga::point_t &p, double r) {
    return Construct::sphere(p, r);
  });
  construct.def("meet", [](const cga::vector_t &p, const cga::vector_t &q) {
    return Construct::meet(p, q);
  });
}

void add_generate(py::module &m) {
  using vsr::cga::Gen;
  auto generate = m.def_submodule("generate");
  generate.def("log", [](const cga::motor_t &m) { return Gen::log(m); });
  generate.def("exp", [](const cga::dual_line_t &b) { return Gen::mot(b); });
  generate.def("outer_exp", [](const cga::dual_line_t &b) {
    return Gen::outer_exponential(b);
  });
  generate.def("cayley",
               [](const cga::dual_line_t &b) { return Gen::cayley(b); });
}

void add_operate(py::module &m) {
  using vsr::cga::Op;
  auto operate = m.def_submodule("operate");
  operate.def("axis_angle", [](const cga::circle_t &c) { return Op::AA(c); });
}

} // namespace cga

} // namespace pyversor
