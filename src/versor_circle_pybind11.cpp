#include <pyversor/pyversor.h>

namespace vsr {

namespace python {

namespace py = pybind11;
using namespace vsr::cga;

void AddCircle(py::module &m) {
  py::class_<Cir>(m, "Cir", py::buffer_protocol())
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double>())
      .def("__init__",
           [](Cir &instance, const Pnt &p, double radius, const Biv &biv) {
             new (&instance) Cir(Construct::circle(p, radius, biv));
           })
      .def("__init__",
           [](Cir &instance, const Pnt &arg1, const Pnt &arg2,
              const Pnt &arg3) { new (&instance) Cir(arg1 ^ arg2 ^ arg3); })
      .def("__getitem__", [](Cir &arg, int idx) { return arg[idx]; })
      .def("__setitem__", [](Cir &arg, int idx, double val) { arg[idx] = val; })
      .def("norm", &Cir::norm)
      .def("rnorm", &Cir::rnorm)
      .def("unit", &Cir::unit)
      .def("__le__", [](const Cir &lhs, const Cir &rhs) { return (lhs <= rhs)[0]; })
      .def("rev", [](Cir &arg) { return ~arg; })
      .def("inv", [](Cir &arg) { return !arg; })
      .def("dual", &Cir::dual)
      .def("undual", &Cir::undual)
      .def("__sub__", [](const Cir &lhs, const Cir &rhs) { return lhs - rhs; })
      .def("axis", [](const Cir &cir) { return Construct::axis(cir); })
      .def("dir",
           [](const Cir &self) { return Round::direction(self).copy<Biv>(); })
      .def("rot",
           [](const Cir &self) {
             Biv b = Round::dir(self).copy<Biv>();
             Rot r = nga::Gen::ratio(Op::dle(b).unit(), Vec::z);
             return r;
           })
      .def("rpo",
           [](const Cir &self) {
             Biv b = Round::dir(self).copy<Biv>();
             Rot r = nga::Gen::ratio(Vec::z, Op::dle(b).unit());
             Pnt location = Round::location(self);
             double radius = Round::radius(self);
             std::vector<double> quat_list{r[3], -r[2], r[1], r[0]};
             std::vector<double> location_list{location[0], location[1],
                                               location[2]};
             return std::make_tuple(radius, location_list, quat_list);
           })
      .def("comm", [](const Cir &lhs,
                      const Cir &rhs) { return (lhs * rhs - rhs * lhs) * 0.5; })
      .def("pnt", [](const Cir &self) { return Round::location(self); })
      .def("radius", [](const Cir &self) { return Round::radius(self); })
      .def("pln", [](const Cir &self) { return Round::carrier(self); })
      .def("surround", [](const Cir &self) { return Round::surround(self); })
      .def("spin", (Cir(Cir::*)(const Mot &) const) & Cir::spin)
      .def("__mul__", [](const Cir &lhs, double rhs) { return lhs * rhs; })
      .def("__div__", [](const Cir &lhs, double rhs) { return lhs / rhs; })
      .def("__repr__",
           [](const Cir &arg) {
             std::stringstream ss;
             ss.precision(4);
             ss << "Cir: [";
             for (int i = 0; i < arg.Num; ++i) {
               ss << " " << arg[i];
             }
             ss << " ]";
             return ss.str();
           })
      .def_buffer([](Cir &arg) -> py::buffer_info {
        return py::buffer_info(&arg.val[0], sizeof(double),
                               py::format_descriptor<double>::format(), 1,
                               {static_cast<unsigned long>(arg.Num)},
                               {sizeof(double)});
      });
}

} // namespace python

} // namespace vsr
