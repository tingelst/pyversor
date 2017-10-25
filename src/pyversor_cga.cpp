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
  add_round(cga);
  add_flat(cga);
  add_construct(cga);
  add_generate(cga);
  add_operate(cga);
}

void add_vector(py::module &m) {
  add_conformal_multivector<vector_t>(m, "Vector")
      .def(py::init<double, double, double, double, double>());
}

void add_bivector(py::module &m) {
  add_conformal_multivector<bivector_t>(m, "Bivector")
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double>());
}

void add_trivector(py::module &m) {
  add_conformal_multivector<trivector_t>(m, "Trivector")
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double>());
}

void add_quadvector(py::module &m) {
  add_conformal_multivector<quadvector_t>(m, "Quadvector")
      .def(py::init<double, double, double, double, double>());
}

void add_motor(py::module &m) {
  add_conformal_multivector<motor_t>(m, "Motor")
      .def(py::init<double, double, double, double, double, double, double,
                    double>())
      .def("rotator", [](const motor_t &arg) { return ega::rotator_t(arg); });
}

void add_dual_line(py::module &m) {
  add_conformal_multivector<dual_line_t>(m, "DualLine")
      .def(py::init<double, double, double, double, double, double>());
}
void add_line(py::module &m) {
  add_conformal_multivector<line_t>(m, "Line").def(
      py::init<double, double, double, double, double, double>());
}

void add_dual_plane(py::module &m) {
  add_conformal_multivector<dual_plane_t>(m, "DualPlane")
      .def(py::init<double, double, double, double>());
}

void add_plane(py::module &m) {
  add_conformal_multivector<plane_t>(m, "Plane")
      .def(py::init<double, double, double, double>());
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
  auto round = m.def_submodule("round");
  round.def("null", [](const ega::vector_t &arg) { return Round::null(arg); });
  round.def("null", [](const cga::vector_t &arg) { return Round::null(arg); });
  round.def("radius",
            [](const cga::dual_sphere_t &arg) { return Round::radius(arg); });
  round.def("radius",
            [](const cga::sphere_t &arg) { return Round::radius(arg); });
  round.def("radius",
            [](const cga::point_pair_t &arg) { return Round::radius(arg); });
  round.def("radius",
            [](const cga::circle_t &arg) { return Round::radius(arg); });

  round.def("center",
            [](const cga::dual_sphere_t &arg) { return Round::center(arg); });
  round.def("center",
            [](const cga::sphere_t &arg) { return Round::center(arg); });
  round.def("center",
            [](const cga::point_pair_t &arg) { return Round::center(arg); });
  round.def("center",
            [](const cga::circle_t &arg) { return Round::center(arg); });

  round.def("location",
            [](const cga::vector_t &arg) { return Round::location(arg); });
  round.def("location",
            [](const cga::quadvector_t &arg) { return Round::location(arg); });

  round.def("location",
            [](const cga::dual_sphere_t &arg) { return Round::location(arg); });
  round.def("location",
            [](const cga::sphere_t &arg) { return Round::location(arg); });
  round.def("location",
            [](const cga::point_pair_t &arg) { return Round::location(arg); });
  round.def("location",
            [](const cga::circle_t &arg) { return Round::location(arg); });
}

void add_flat(py::module &m) {
  using vsr::cga::Flat;
  auto flat = m.def_submodule("flat");
  flat.def("location", [](const dual_plane_t &a, const point_t &b) {
    return Flat::location(a, b, true);
  });
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
}

void add_operate(py::module &m) {
  using vsr::cga::Op;
  auto operate = m.def_submodule("operate");
  operate.def("axis_angle", [](const cga::circle_t &c) { return Op::AA(c); });
}

} // namespace cga

} // namespace pyversor
