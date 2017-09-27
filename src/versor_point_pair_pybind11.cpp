#include <pyversor/pyversor.h>

namespace vsr {

namespace python {

namespace py = pybind11;
using namespace vsr::cga;

template <typename T>
py::class_<T> add(py::module &m, const std::string &type_name) {
  auto t = py::class_<T>(m, type_name, py::buffer_protocol());
  t.def("dual", &T::dual);
  t.def("__getitem__", [](Par &arg, int idx) { return arg[idx]; });
  t.def("__setitem__", [](Par &arg, int idx, double val) { arg[idx] = val; });
  t.def_buffer([](T &arg) {
    return py::buffer_info(
        &arg.val[0], sizeof(double), py::format_descriptor<double>::format(), 1,
        {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
  });
}

void AddPointPair(py::module &m) {
  py::class_<Par>(m, "Par", py::buffer_protocol())
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double>())
      .def("__init__",
           [](Par &instance, const Pnt &arg1, const Pnt &arg2) { new (&instance) Par(arg1 ^ arg2); })
      .def("__getitem__", [](Par &arg, int idx) { return arg[idx]; })
      .def("__setitem__", [](Par &arg, int idx, double val) { arg[idx] = val; })
      .def("norm", &Par::norm)
      .def("rnorm", &Par::rnorm)
      .def("unit", &Par::unit)
      .def("rev", [](Par &arg) { return ~arg; })
      .def("inv", [](Par &arg) { return !arg; })
      .def("dual", &Par::dual)
      .def("undual", &Par::undual)
      .def("__sub__", [](const Par &lhs, const Par &rhs) { return lhs - rhs; })
      .def("axis", [](const Par &cir) { return Construct::axis(cir); })
      .def("dir",
           [](const Par &self) { return Round::direction(self).copy<Biv>(); })
      .def("rot",
           [](const Par &self) {
             Biv b = Round::dir(self).copy<Biv>();
             Rot r = nga::Gen::ratio(Op::dle(b).unit(), Vec::z);
             return r;
           })
      .def("rpo",
           [](const Par &self) {
             Biv b = Round::dir(self).copy<Biv>();
             Rot r = nga::Gen::ratio(Vec::z, Op::dle(b).unit());
             Pnt location = Round::location(self);
             double radius = Round::radius(self);
             std::vector<double> quat_list{r[3], -r[2], r[1], r[0]};
             std::vector<double> location_list{location[0], location[1],
                                               location[2]};
             return std::make_tuple(radius, location_list, quat_list);
           })
      .def("comm", [](const Par &lhs,
                      const Par &rhs) { return (lhs * rhs - rhs * lhs) * 0.5; })
      .def("pnt", [](const Par &self) { return Round::location(self); })
        .def("print", &Par::print)
      .def("radius", [](const Par &self) { return Round::radius(self); })
      .def("pln", [](const Par &self) { return Round::carrier(self); })
      .def("surround", [](const Par &self) { return Round::surround(self); })
      .def("spin", (Par(Par::*)(const Mot &) const) & Par::spin)
      .def("__mul__", [](const Par &lhs, double rhs) { return lhs * rhs; })
      .def("__div__", [](const Par &lhs, double rhs) { return lhs / rhs; })
      .def("__repr__",
           [](const Par &arg) {
             std::stringstream ss;
             ss.precision(4);
             ss << "Par: [";
             for (int i = 0; i < arg.Num; ++i) {
               ss << " " << arg[i];
             }
             ss << " ]";
             return ss.str();
           })
      .def_buffer([](Par &arg) -> py::buffer_info {
        return py::buffer_info(&arg.val[0], sizeof(double),
                               py::format_descriptor<double>::format(), 1,
                               {static_cast<unsigned long>(arg.Num)},
                               {sizeof(double)});
      });
}

} // namespace python

} // namespace vsr
