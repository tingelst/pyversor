#include <pyversor/pyversor.h>

namespace pyversor {

namespace cga {

void add_submodule(py::module &m) {
  auto cga = m.def_submodule("cga");
  add_vector(cga);
  add_bivector(cga);
  add_trivector(cga);
  add_quadvector(cga);
  add_multivector(cga);
  add_motor(cga);
  add_dual_line(cga);
  add_line(cga);
  add_dual_plane(cga);
  add_plane(cga);
  // add_direction_vector(cga);
  // add_direction_bivector(cga);
  // add_direction_trivector(cga);
  add_round(cga);
  add_flat(cga);
  add_construct(cga);
  add_generate(cga);
  add_operate(cga);
}

struct round {
  template <typename round_t, typename module_t = py::module>
  static void add_distance(module_t &m) {
    using vsr::cga::Round;
    m.def("distance", [](const round_t &a, const round_t &b) {
      return Round::distance(a, b);
    });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_squared_distance(module_t &m) {
    using vsr::cga::Round;
    m.def("squared_distance", [](const round_t &a, const round_t &b) {
      return Round::squaredDistance(a, b);
    });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_location(module_t &m) {
    using vsr::cga::Round;
    m.def("location", [](const round_t &a) { return Round::location(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_center(module_t &m) {
    using vsr::cga::Round;
    m.def("center", [](const round_t &a) { return Round::center(a); });
  }

  template <typename round_t, bool dual, typename module_t = py::module>
  static void add_size(module_t &m) {
    using vsr::cga::Round;
    m.def("size", [](const round_t &a) { return Round::size(a, dual); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_radius(module_t &m) {
    using vsr::cga::Round;
    m.def("radius", [](const round_t &a) { return Round::radius(a); });
    // Inverse of radius
    m.def("curvature", [](const round_t &a) { return Round::curvature(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_null(module_t &m) {
    using vsr::cga::Round;
    m.def("null", [](const round_t &a) { return Round::null(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_carrier(module_t &m) {
    using vsr::cga::Round;
    m.def("carrier", [](const round_t &a) { return Round::carrier(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_normalize(module_t &m) {
    using vsr::cga::Round;
    m.def("normalize", [](const round_t &a) { return Round::normalize(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_renormalize(module_t &m) {
    using vsr::cga::Round;
    m.def("renormalize",
          [](const round_t &a) { return Round::renormalize(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_surround(module_t &m) {
    using vsr::cga::Round;
    m.def("surround", [](const round_t &a) { return Round::surround(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_direction(module_t &m) {
    using vsr::cga::Round;
    m.def("direction", [](const round_t &a) { return Round::direction(a); });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_split(module_t &m) {
    using vsr::cga::Round;
    m.def("split", [](const round_t &a) { return Round::split(a); });
    m.def("split_location",
          [](const round_t &a) { return Round::splitLocation(a); });
  }

  template <typename round_t = dual_sphere_t, typename module_t = py::module>
  static void add_produce(module_t &m) {
    using vsr::cga::Round;
    m.def("produce", [](const round_t &a, const ega::vector_t &b) {
      return Round::produce(a, b);
    });
    m.def("produce", [](const round_t &a, const ega::bivector_t &b) {
      return Round::produce(a, b);
    });
  }

  template <typename round_t, typename module_t = py::module>
  static void add_radius_center_location(module_t &m) {
    add_radius<round_t>(m);
    add_center<round_t>(m);
    add_location<round_t>(m);
  }
};

void add_vector(py::module &m) {
  auto t = add_conformal_multivector<vector_t>(m, "Vector");
  t.def(py::init<double, double, double, double, double>());
  round::add_null<vector_t>(t);
  round::add_radius_center_location<vector_t>(t);
  round::add_produce<vector_t>(t);
  round::add_normalize<vector_t>(t);
  round::add_distance<vector_t>(t);
  round::add_squared_distance<vector_t>(t);
  round::add_size<vector_t, true>(t);
}

void add_bivector(py::module &m) {
  auto t = add_conformal_multivector<bivector_t>(m, "Bivector");
  t.def(py::init<double, double, double, double, double, double, double, double,
                 double, double>());
  round::add_radius_center_location<bivector_t>(t);
  round::add_carrier<bivector_t>(t);
  round::add_surround<bivector_t>(t);
  round::add_normalize<bivector_t>(t);
  round::add_renormalize<bivector_t>(t);
  round::add_direction<bivector_t>(t);
  round::add_split<bivector_t>(t);
  round::add_size<bivector_t, true>(t);
}

void add_trivector(py::module &m) {
  auto t = add_conformal_multivector<trivector_t>(m, "Trivector");
  t.def(py::init<double, double, double, double, double, double, double, double,
                 double, double>());
  round::add_radius_center_location<trivector_t>(t);
  round::add_carrier<trivector_t>(t);
  round::add_surround<trivector_t>(t);
  round::add_normalize<trivector_t>(t);
  round::add_renormalize<trivector_t>(t);
  round::add_direction<trivector_t>(t);
  round::add_split<trivector_t>(t);
  round::add_size<trivector_t, false>(t);
}

void add_quadvector(py::module &m) {
  auto t = add_conformal_multivector<quadvector_t>(m, "Quadvector");
  t.def(py::init<double, double, double, double, double>());
  round::add_radius_center_location<quadvector_t>(t);
  round::add_normalize<quadvector_t>(t);
  round::add_size<quadvector_t, false>(t);
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

}  // namespace cga

}  // namespace pyversor
