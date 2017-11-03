void add_construct(py::module &m) {
  using vsr::cga::Construct;
  auto construct = m.def_submodule("construct");
  construct.def("sphere", [](const cga::point_t &p, double r) {
    return Construct::sphere(p, r);
  });
  construct.def("meet", [](const cga::vector_t &p, const cga::vector_t &q) {
    return Construct::meet(p, q);
  });
}
