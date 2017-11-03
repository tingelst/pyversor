#include <pyversor/tangents.h>

namespace pyversor {

namespace cga {

void def_tangents(py::module &m) {
  auto tangents = m.def_submodule("tangents");
  def_tangent_vector(tangents);
  def_tangent_bivector(tangents);
  def_tangent_trivector(tangents);
}

void def_tangent_vector(py::module &m) {
  auto drv = def_multivector<cga::tangent_vector_t>(m, "TangentVector");
}
void def_tangent_bivector(py::module &m) {
  auto drb = def_multivector<cga::tangent_bivector_t>(m, "TangentBivector");
}

void def_tangent_trivector(py::module &m) {
  auto drt = def_multivector<cga::tangent_trivector_t>(m, "TangentTrivector");
}

} // namespace cga

} // namespace pyversor
