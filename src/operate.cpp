void add_operate(py::module &m) {
  using vsr::cga::Op;
  auto operate = m.def_submodule("operate");
  operate.def("axis_angle", [](const cga::circle_t &c) { return Op::AA(c); });
}
