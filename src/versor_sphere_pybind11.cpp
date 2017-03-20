#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    void AddSphere(py::module &m) {
      py::class_<Sph>(m, "Sph", py::buffer_protocol())
        .def(py::init<double, double, double, double, double>())
        .def("__init__",
             [](Sph &instance, const Pnt &p, double radius) {
               new (&instance) Sph(nga::Round::sphere(p, radius).undual());
             })
        .def("__init__",
             [](Sph &instance, const Pnt &p1, const Pnt &p2, const Pnt &p3,
                const Pnt &p4) { new (&instance) Sph(p1 ^ p2 ^ p3 ^ p4); })
        .def("__getitem__", [](Sph &arg, int idx){return arg[idx];})
        .def("__setitem__", [](Sph &arg, int idx, double val) { arg[idx] = val; })
        .def("norm", &Sph::norm)
        .def("rnorm", &Sph::rnorm)
        .def("unit", &Sph::unit)
        .def("rev", [](Sph &arg){return ~arg;})
        .def("inv", [](Sph &arg){return !arg;})
        .def("dual", &Sph::dual)
        .def("undual", &Sph::undual)
        .def("spin", (Sph (Sph::*)(const Rot &) const) & Sph::spin)
        .def("spin", (Sph (Sph::*)(const Mot &) const) & Sph::spin)
        .def("pnt", [](const Sph &self) { return nga::Round::location(self); })
        .def("radius", [](const Sph &self) { return nga::Round::radius(self); })
        .def("meet",
             [](const Sph &self, const Sph &other) {
               return Construct::meet(self.dual(), other.dual());
             })
        .def("__repr__",
             [](const Sph &arg) {
               std::stringstream ss;
               ss.precision(4);
               ss << "Sph: [";
               for (int i = 0; i < arg.Num; ++i) {
                 ss << " " << arg[i];
               }
               ss << " ]";
               return ss.str();
             })
        .def_buffer([](Sph &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
