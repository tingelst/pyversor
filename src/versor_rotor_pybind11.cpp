#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    void AddRotor(py::module &m) {
      py::class_<Rot>(m, "Rot", py::buffer_protocol())
        .def("__init__", [](Rot &instance,
                            Biv &arg) { new (&instance) Rot(Gen::rotor(arg)); },
             "Bivector logarithm: R = exp(B)")
        .def(py::init<double, double, double, double>())
        .def("__getitem__", [](Rot &arg, int idx){return arg[idx];})
        .def("__setitem__", [](Rot &arg, int idx, double val) { arg[idx] = val; })
        .def("unit", &Rot::unit)
        .def("rev", [](Rot &arg){return ~arg;})
        .def("inv", [](Rot &arg){return !arg;})
        .def("log", [](const Rot &arg) { return Gen::log(arg); })
        .def("biv", [](const Rot &arg) { return Biv(arg); })
        .def("ratio", [](const Vec &a, const Vec &b) { return Gen::ratio(a, b); })
        .def("__neg__", [](const Rot &arg) { return -arg; })
        .def("__mul__", [](const Rot &lhs, double rhs) { return lhs * rhs; })
        .def("__mul__", [](const Rot &lhs, const Biv &rhs) { return lhs * rhs; })
        .def("__mul__", [](const Rot &lhs, const Trs &rhs) { return lhs * rhs; })
        .def("__mul__", [](const Rot &lhs, const Rot &rhs) { return lhs * rhs; })
        .def("__repr__",
             [](const Rot &arg) {
               std::stringstream ss;
               ss.precision(2);
               ss << "Rot: [";
               for (int i = 0; i < arg.Num; ++i) {
                 ss << " " << arg[i];
               }
               ss << " ]";
               return ss.str();
             })
        .def_buffer([](Rot &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
