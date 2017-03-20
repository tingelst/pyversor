#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    void AddLine(py::module &m) {
      py::class_<Lin>(m, "Lin", py::buffer_protocol())
        .def(py::init<double, double, double, double, double, double>())
        .def("__init__",
             [](Lin &instance, const Vec &arg1, const Vec &arg2) {
               new (&instance) Lin(Construct::line(arg1, arg2));
             })
        .def("__init__",
             [](Lin &instance, const Pnt &arg1, const Pnt &arg2) {
               new (&instance) Lin(Construct::line(arg1, arg2));
             })
        .def("__init__",
             [](Lin &instance, const Pnt &arg1, const Vec &arg2) {
               new (&instance) Lin(arg1 ^ arg2 ^ Inf(1.0));
             })
        .def("__init__", [](Lin &instance,
                            const Cir &circle) { new (&instance) Dll(circle); })
        .def("__getitem__", [](Lin &arg, int idx){return arg[idx];})
        .def("__setitem__", [](Lin &arg, int idx, double val) { arg[idx] = val; })
        .def("norm", &Lin::norm)
        .def("rnorm", &Lin::rnorm)
        .def("unit", &Lin::unit)
        .def("rev", [](Lin &arg){return ~arg;})
        .def("inv", [](Lin &arg){return !arg;})
        .def("dir", [](const Lin &arg) { return -(Ori(1.0) ^ Inf(1.0)) <= arg; })
        .def("meet", [](const Lin &self,
                        const Lin &lin) { return Construct::meet(self, lin); })
        .def("biv",
             [](const Lin &arg) {
               return -(Ori(1.0) ^ Inf(1.0)) <= (arg ^ Ori(1.));
             })
        .def("loc",
             [](const Lin &arg, const Pnt &arg2) {
               return Flat::location(arg, arg2, false);
             })
        .def("reflect_in_line",
             [](const Lin &self, const Lin &other) { return self.reflect(other); })
        .def("spin", (Lin (Lin::*)(const Rot &) const) & Lin::spin)
        .def("spin", (Lin (Lin::*)(const Mot &) const) & Lin::spin)
        .def("__mul__", [](const Lin &lhs, const Lin &rhs) { return lhs * rhs; })
        .def("dual", &Lin::dual)
        .def("undual", &Lin::undual)
        .def("__repr__", [](const Lin &arg) {
            std::stringstream ss;
            ss.precision(4);
            ss << "Lin: [";
            for (int i = 0; i < arg.Num; ++i) {
              ss << " " << arg[i];
            }
            ss << " ]";
            return ss.str();
          })
        .def_buffer([](Lin &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
