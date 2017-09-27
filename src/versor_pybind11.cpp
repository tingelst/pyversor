#include <pyversor/pyversor.h>

namespace vsr {

namespace python {

namespace py = pybind11;
using namespace vsr::cga;

// Forward declarations
void AddScalar(py::module &m);
void AddVector(py::module &m);
void AddBivector(py::module &m);
void AddRotor(py::module &m);
void AddPoint(py::module &m);
void AddLine(py::module &m);
void AddDualLine(py::module &m);
void AddTranslator(py::module &m);
void AddMotor(py::module &m);
void AddDualPlane(py::module &m);
void AddPlane(py::module &m);
void AddCircle(py::module &m);
void AddPointPair(py::module &m);
void AddSphere(py::module &m);
void AddTrivector(py::module &m);
void AddCGA(py::module &m);
void AddEGA(py::module &m);

PYBIND11_PLUGIN(pyversor) {
  py::module m("pyversor", "versor plugin");
  AddVector(m);
  AddBivector(m);
  AddRotor(m);
  AddPoint(m);
  AddLine(m);
  AddDualLine(m);
  AddTranslator(m);
  AddMotor(m);
  AddDualPlane(m);
  AddPlane(m);
  AddCircle(m);
  AddPointPair(m);
  AddSphere(m);
  AddCGA(m);
  AddEGA(m);

  return m.ptr();
}

} // namespace python

} // namespace vsr
