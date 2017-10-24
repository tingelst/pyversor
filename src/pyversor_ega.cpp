#include <pyversor/pyversor.h>

namespace pyversor {

namespace ega {

void add_submodule(py::module &m) {
  auto ega = m.def_submodule("ega");
  add_vector(ega);
  add_bivector(ega);
  add_trivector(ega);
  add_rotator(ega);
  add_multivector(ega);
}

void add_vector(py::module &m) {
  add_euclidean_multivector<vector_t>(m, "Vector")
      .def(py::init<double, double, double>())
      .def("null", &vector_t::null);
}

void add_bivector(py::module &m) {
  add_euclidean_multivector<bivector_t>(m, "Bivector")
      .def(py::init<double, double, double>());
}

void add_trivector(py::module &m) {
  add_euclidean_multivector<trivector_t>(m, "Trivector")
      .def(py::init<double>());
}

void add_rotator(py::module &m) {
  add_euclidean_multivector<rotator_t>(m, "Rotator")
      .def(py::init<double, double, double, double>());
}

void add_multivector(py::module &m) {
  add_euclidean_multivector<multivector_t>(m, "Multivector")
      .def(py::init<>())
      .def(py::init<double, double, double, double, double, double, double,
                    double>());
}

} // namespace ega

} // namespace pyversor