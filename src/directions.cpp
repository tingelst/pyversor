#include <pyversor/directions.h>

namespace pyversor {

namespace cga {

void def_directions(py::module &m) {
  auto dir = m.def_submodule("directions");
  def_direction_vector(dir);
  def_direction_bivector(dir);
  def_direction_trivector(dir);
}

void def_direction_vector(py::module &m) {
  auto drv = def_multivector<cga::direction_vector_t>(m, "DirectionVector");
  drv.def(py::init<double, double, double>());
}

void def_direction_bivector(py::module &m) {
  auto drb = def_multivector<cga::direction_bivector_t>(m, "DirectionBivector");
  drb.def(py::init<double, double, double>());
}

void def_direction_trivector(py::module &m) {
  auto drt =
      def_multivector<cga::direction_trivector_t>(m, "DirectionTrivector");
  drt.def(py::init<double>());
}

} // namespace cga

} // namespace pyversor
