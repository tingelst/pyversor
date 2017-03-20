
#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;


    void AddDualLine(py::module &m) {
      py::class_<Dll>(m, "Dll", py::buffer_protocol())
        .def(py::init<double, double, double, double, double, double>())
        .def("__init__",
             [](Dll &instance, const Pnt &arg1, const Pnt &arg2) {
               new (&instance) Dll(Construct::line(arg1, arg2).dual());
             })
        .def("__init__",
             [](Dll &instance, const Pnt &arg1, const Vec &arg2) {
               new (&instance) Dll(Construct::line(arg1, arg2).dual());
             })
        .def("__getitem__", [](Dll &arg, int idx){return arg[idx];})
        .def("__setitem__", [](Dll &arg, int idx, double val) { arg[idx] = val; })
        .def("norm", &Dll::norm)
        .def("rnorm", &Dll::rnorm)
        .def("unit", &Dll::unit)
        .def("rev", [](Dll &arg){return ~arg;})
        .def("inv", [](Dll &arg){return !arg;})
        .def("dual", &Dll::dual)
        .def("undual", &Dll::undual)
        .def("comm",
             [](const Dll &lhs, const Dll &rhs) {
               return Dll(lhs * rhs - rhs * lhs) * 0.5;
             })
        .def("comm", [](const Dll &lhs,
                        const Mot &rhs) { return (lhs * rhs - rhs * lhs) * 0.5; })
        .def("acomm",
             [](const Dll &lhs, const Mot &rhs) {
               return (lhs * rhs + rhs * lhs) * 0.5;
             })
        .def("comm",
             [](const Dll &lhs, const Pnt &rhs) {
               return Pnt((lhs * rhs - rhs * lhs) * 0.5);
             })
        .def("acomm",
             [](const Dll &lhs, const Pnt &rhs) {
               return Pnt((lhs * rhs + rhs * lhs) * 0.5);
             })
        .def("ratio",
             [](const Dll &self, const Dll &other, double amount) {
               return Gen::ratio(self, other, amount);
             })

        .def("meet", [](const Dll &self,
                        const Dlp &dlp) { return Construct::meet(self, dlp); })

        .def("meet", [](const Dll &self,
                        const Dll &dll) { return Construct::meet(self, dll); })
        .def("drv", [](const Dll &arg) { return Drv(arg); })
        .def("biv", [](const Dll &arg) { return Biv(arg); })
        .def("spin", (Dll(Dll::*)(const Mot &) const) & Dll::spin)
        .def("exp", [](const Dll &arg) { return Gen::motor(arg); })
        .def("loc",
             [](const Dll &arg, const Pnt &arg2) {
               return Flat::location(arg, arg2, true);
             })
        .def("dir", [](const Dll &arg) { return Flat::direction(arg.undual()); })
        .def("__neg__", [](const Dll &arg) { return -arg; })
        .def("__add__", [](const Dll &lhs, const Dll &rhs) { return lhs + rhs; })
        .def("__sub__", [](const Dll &lhs, const Dll &rhs) { return lhs - rhs; })
        .def("__mul__", [](const Dll &lhs, const Mot &rhs) { return lhs * rhs; })
        .def("__mul__", [](const Dll &lhs, const Dll &rhs) { return lhs * rhs; })
        .def("__le__",
             [](const Dll &lhs, const Dll &rhs) { return (lhs <= rhs)[0]; })
        .def("__xor__",
             [](const Dll &lhs, const Dll &rhs) { return Mot(lhs ^ rhs); })
        .def("__mul__", [](const Dll &lhs, double rhs) { return lhs * rhs; })
        .def("__div__", [](const Dll &lhs, double rhs) { return lhs / rhs; })
        .def("__repr__",
             [](const Dll &arg) {
               std::stringstream ss;
               ss.precision(4);
               ss << "Dll: [";
               for (int i = 0; i < arg.Num; ++i) {
                 ss << " " << arg[i];
               }
               ss << " ]";
               return ss.str();
             })
        .def_buffer([](Dll &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
