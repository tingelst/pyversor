#include <pyversor/versors.h>

namespace pyversor {

namespace cga {

void def_versors(py::module &m) {
  auto versors = m.def_submodule("versors");
  def_rotator(versors);
  def_translator(versors);
  def_motor(versors);
  def_conformal_rotor(versors);
  def_boost(versors);
}

void def_rotator(py::module &m) {
  auto rot = def_multivector<ega::rotator_t>(m, "Rotator");
}

void def_translator(py::module &m) {
  auto trs = def_multivector<cga::translator_t>(m, "Translator");
}

void def_motor(py::module &m) {
  auto mot = def_multivector<cga::motor_t>(m, "Motor");
}

void def_conformal_rotor(py::module &m) {
  auto con = def_multivector<conformal_rotor_t>(m, "ConformalRotor");
}

void def_boost(py::module &m) {
  auto bst = def_multivector<boost_t>(m, "Boost");
}

} // namespace cga

} // namespace pyversor
