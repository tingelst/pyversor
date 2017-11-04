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
  def_geometric_product<ega::rotator_t, ega::rotator_t>(rot);
  def_geometric_product<ega::rotator_t, cga::translator_t>(rot);
  def_geometric_product<ega::rotator_t, cga::motor_t>(rot);
}

void def_translator(py::module &m) {
  auto trs = def_multivector<cga::translator_t>(m, "Translator");
  def_geometric_product<cga::translator_t, cga::translator_t>(trs);
  def_geometric_product<cga::translator_t, cga::motor_t>(trs);
  def_geometric_product<cga::translator_t, ega::rotator_t>(trs);
}

void def_motor(py::module &m) {
  auto mot = def_multivector<cga::motor_t>(m, "Motor");
  def_geometric_product<cga::motor_t, cga::motor_t>(mot);
  def_geometric_product<cga::motor_t, cga::translator_t>(mot);
  def_geometric_product<cga::motor_t, ega::rotator_t>(mot);
}

void def_conformal_rotor(py::module &m) {
  auto con = def_multivector<conformal_rotor_t>(m, "ConformalRotor");
  def_geometric_product<cga::conformal_rotor_t, cga::conformal_rotor_t>(con);
}

void def_boost(py::module &m) {
  auto bst = def_multivector<boost_t>(m, "Boost");
  def_geometric_product<cga::boost_t, cga::boost_t>(bst);
}

}  // namespace cga

}  // namespace pyversor
