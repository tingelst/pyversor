#include <pyversor/multivectors.h>
#include <pyversor/products.h>

namespace pyversor {

namespace cga {

void def_vector(py::module &m) {
  auto vec = def_multivector<cga::vector_t>(m, "Vector");
  vec.def(py::init<double, double, double, double, double>());
  def_geometric_product<cga::vector_t, cga::vector_t>(vec);
}

void def_bivector(py::module &m) {
  auto biv = def_multivector<cga::bivector_t>(m, "Bivector");
  biv.def(py::init<double, double, double, double, double, double, double,
                   double, double, double>());
  biv.def(py::init<cga::dual_line_t>());
  biv.def(py::init<cga::direction_vector_t>());
  biv.def(py::init<cga::tangent_vector_t>());
  def_geometric_product<cga::bivector_t, cga::bivector_t>(biv);
}

void def_trivector(py::module &m) {
  auto tri = def_multivector<cga::trivector_t>(m, "Trivector");
  tri.def(py::init<double, double, double, double, double, double, double,
                   double, double, double>());
  def_geometric_product<cga::trivector_t, cga::trivector_t>(tri);
}

void def_quadvector(py::module &m) {
  auto quad = def_multivector<cga::quadvector_t>(m, "Quadvector");
  quad.def(py::init<double, double, double, double, double>());
  def_geometric_product<cga::quadvector_t, cga::quadvector_t>(quad);
}

void def_pseudoscalar(py::module &m) {
  auto pss = def_multivector<cga::pseudoscalar_t>(m, "Pseudoscalar");
  pss.def(py::init<double>());
}

void def_infinity(py::module &m) {
  auto inf = def_multivector<cga::infinity_t>(m, "Infinity");
  inf.def(py::init<double>());
}

void def_origin(py::module &m) {
  auto ori = def_multivector<cga::origin_t>(m, "Origin");
  ori.def(py::init<double>());
}

void def_full_multivector(py::module &m) {
  def_multivector<multivector_t>(m, "Multivector")
      .def(py::init<>())
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double, double, double, double,
                    double, double, double, double>());
}

} // namespace cga
} // namespace pyversor