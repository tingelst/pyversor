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
                    double>());
}

void add_screw(py::module &m) {
  add_conformal_multivector<screw_t>(m, "Screw")
      .def(py::init<double, double, double, double, double, double>());
}

void add_multivector(py::module &m) {
  add_conformal_multivector<multivector_t>(m, "Multivector").def(py::init<>());
}

} // namespace cga

} // namespace pyversor
