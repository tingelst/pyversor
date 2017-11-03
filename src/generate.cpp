void add_generate(py::module &m) {
  using vsr::cga::Gen;
  auto generate = m.def_submodule("generate");
  generate.def("log", [](const cga::motor_t &m) { return Gen::log(m); });
  generate.def("exp", [](const cga::dual_line_t &b) { return Gen::mot(b); });
  generate.def("outer_exp", [](const cga::dual_line_t &b) {
    return Gen::outer_exponential(b);
  });
  generate.def("cayley",
               [](const cga::dual_line_t &b) { return Gen::cayley(b); });
}
