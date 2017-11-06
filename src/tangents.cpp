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
  auto tnv = def_multivector<cga::tangent_vector_t>(m, "TangentVector");
  tnv.def(py::init<double, double, double>());
  def_sandwich_product<cga::tangent_vector_t, cga::translator_t, cga::bivector_t>(tnv);
}
void def_tangent_bivector(py::module &m) {
  auto tnb = def_multivector<cga::tangent_bivector_t>(m, "TangentBivector");
  tnb.def(py::init<double, double, double>());
}

void def_tangent_trivector(py::module &m) {
  auto tnt = def_multivector<cga::tangent_trivector_t>(m, "TangentTrivector");
  tnt.def(py::init<double>());
}

} // namespace cga

} // namespace pyversor
