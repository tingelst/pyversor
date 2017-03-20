#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    using EGA = vsr::Multivector<vsr::algebra<vsr::metric<4, 1, true>, double>,
                                 vsr::Basis<0, 1, 2, 4, 3, 5, 6, 7>>;

    void AddEGA(py::module &m) {
      py::class_<EGA>(m, "EGA", py::buffer_protocol())
        .def(py::init<double, double, double, double, double, double, double,
             double>())
        .def("__init__",
             [](EGA &instance, EGA &arg) { new (&instance) EGA(arg); })
        .def("__init__",
             [](EGA &instance, Vec &arg) { new (&instance) EGA(arg); })
        .def("__init__",
             [](EGA &instance, Biv &arg) { new (&instance) EGA(arg); })
        .def("__init__",
             [](EGA &instance, Tri &arg) { new (&instance) EGA(arg); })
        .def("__init__",
             [](EGA &instance, Rot &arg) { new (&instance) EGA(arg); })
        .def("__getitem__", [](EGA &arg, int idx){return arg[idx];})
        .def("__setitem__", [](EGA &arg, int idx, double val) { arg[idx] = val; })
        .def("norm", &EGA::norm)
        .def("rnorm", &EGA::rnorm)
        .def("unit", &EGA::unit)
        .def("rev", [](EGA &arg){return ~arg;})
        .def("inv", [](EGA &arg){return !arg;})
        .def("dual", &EGA::dual)
        .def("undual", &EGA::undual)
        .def("duale", &EGA::duale)
        .def("unduale", &EGA::unduale)
        .def("comm",
             [](const EGA &lhs, const EGA &rhs) {
               return EGA(lhs * rhs - rhs * lhs) * 0.5;
             })
        .def("acomm",
             [](const EGA &lhs, const EGA &rhs) {
               return EGA(lhs * rhs + rhs * lhs) * 0.5;
             })
        .def("__add__",
             [](const EGA &lhs, const EGA &rhs) { return EGA(lhs + rhs); })
        .def("__sub__",
             [](const EGA &lhs, const EGA &rhs) { return EGA(lhs - rhs); })
        .def("__mul__",
             [](const EGA &lhs, const EGA &rhs) { return EGA(lhs * rhs); })
        .def("__mul__",
             [](const EGA &lhs, double &rhs) { return EGA(lhs * rhs); })
        .def("__rmul__",
             [](const EGA &lhs, double &rhs) { return EGA(lhs * rhs); })
        .def("__le__",
             [](const EGA &lhs, const EGA &rhs) { return EGA(lhs <= rhs); })
        .def("__xor__",
             [](const EGA &lhs, const EGA &rhs) { return EGA(lhs ^ rhs); })
        .def("spin", (EGA (EGA::*)(const EGA &) const) & EGA::spin)
        .def("__repr__",
             [](const EGA &arg) {
               std::stringstream ss;
               ss.precision(2);
               ss << "EGA: [";
               for (int i = 0; i < arg.Num; ++i) {
                 ss << " " << arg[i];
               }
               ss << " ]";
               return ss.str();
             })
        .def_buffer([](EGA &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
