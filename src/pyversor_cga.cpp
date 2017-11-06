#include <pyversor/pyversor.h>

namespace pyversor {

namespace cga {

void add_submodule(py::module &m) {
  auto cga = m.def_submodule("cga");
  def_vector(cga);
  def_bivector(cga);
  def_trivector(cga);
  def_quadvector(cga);
  def_pseudoscalar(cga);
  def_infinity(cga);
  def_origin(cga);
  def_full_multivector(cga);
  def_rounds(cga);
  def_flats(cga);
  def_directions(cga);
  def_tangents(cga);
  def_versors(cga);

  // add_construct(cga);
  def_generate(cga);
  // add_operate(cga);
}

} // namespace cga

} // namespace pyversor
