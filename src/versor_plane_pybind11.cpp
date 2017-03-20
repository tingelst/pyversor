#include <pyversor/pyversor.h>
namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    void AddPlane(py::module &m) {
      py::class_<Pln>(m, "Pln", py::buffer_protocol())
        .def(py::init<double, double, double, double>())
        .def(
             "__init__",
             [](Pln &instance, const Pnt &arg1, const Pnt &arg2, const Pnt &arg3) {
               new (&instance) Pln(Construct::plane(arg1, arg2, arg3));
             })
        .def("__getitem__", [](Pln &arg, int idx){return arg[idx];})
        .def("__setitem__", [](Pln &arg, int idx, double val) { arg[idx] = val; })
        .def("norm", &Pln::norm)
        .def("rnorm", &Pln::rnorm)
        .def("unit", &Pln::unit)
        .def("rev", [](Pln &arg){return ~arg;})
        .def("inv", [](Pln &arg){return !arg;})
        .def("dual", &Pln::dual)
        .def("undual", &Pln::undual)
        .def("loc",
             [](const Pln &arg, const Pnt &arg2) {
               return Flat::location(arg, arg2, false);
             })
        .def("spin", (Pln (Pln::*)(const Mot &) const) & Pln::spin)
        .def("__mul__", [](const Pln &lhs, double rhs) { return lhs * rhs; })
        .def("__mul__", [](const Pln &lhs, const Pln &rhs) { return lhs * rhs; })
        .def("__div__", [](const Pln &lhs, double rhs) { return lhs / rhs; })
        .def("__leq__", [](const Pln &lhs, const Pln &rhs) { return lhs <= rhs; })
        .def("__repr__",
             [](const Pln &arg) {
               std::stringstream ss;
               ss.precision(4);
               ss << "Pln: [";
               for (int i = 0; i < arg.Num; ++i) {
                 ss << " " << arg[i];
               }
               ss << " ]";
               return ss.str();
             })
        .def_buffer([](Pln &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
