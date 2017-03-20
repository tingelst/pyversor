#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    void AddTranslator(py::module &m) {
      py::class_<Trs>(m, "Trs", py::buffer_protocol())
        .def(py::init<double, double, double, double>())
        .def("__getitem__", [](Trs &arg, int idx){return arg[idx];})
        .def("__setitem__", [](Trs &arg, int idx, double val) { arg[idx] = val; })
        .def("rev", [](Trs &arg){return ~arg;})
        .def("inv", [](Trs &arg){return !arg;})
        .def("__mul__", [](const Trs &lhs, const Rot &rhs) { return lhs * rhs; })
        .def("__mul__", [](const Trs &lhs, const Mot &rhs) { return lhs * rhs; })
        .def("__repr__", [](const Trs &arg) {
            std::stringstream ss;
            ss.precision(4);
            ss << "Trs: [";
            for (int i = 0; i < arg.Num; ++i) {
              ss << " " << arg[i];
            }
            ss << " ]";
            return ss.str();
          })
      .def_buffer([](Trs &arg) -> py::buffer_info {
          return py::buffer_info(
                                 &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                 1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
        });
    }

  }  // namespace python

}  // namespace vsr
