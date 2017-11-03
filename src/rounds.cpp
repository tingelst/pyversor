#include <pyversor/rounds.h>

namespace pyversor {

namespace cga {

void def_rounds(py::module &m) {
  using vsr::cga::Round;
  auto t = m.def_submodule("rounds");
  round::def_null<ega::vector_t>(t);
  round::def_null<cga::vector_t>(t);
  round::def_distance<vector_t>(m);
  round::def_squared_distance<vector_t>(m);
  round::def_radius_center_location<dual_sphere_t>(t);
  round::def_radius_center_location<sphere_t>(t);
  round::def_radius_center_location<point_pair_t>(t);
  round::def_radius_center_location<circle_t>(t);

  round::def_normalize<dual_sphere_t>(t);
  round::def_normalize<sphere_t>(t);
  round::def_normalize<point_pair_t>(t);
  round::def_normalize<circle_t>(t);

  round::def_size<dual_sphere_t, true>(t);
  round::def_size<sphere_t, false>(t);
  round::def_size<point_pair_t, true>(t);
  round::def_size<circle_t, false>(t);

  round::def_carrier<point_pair_t>(t);
  round::def_carrier<circle_t>(t);
  round::def_surround<point_pair_t>(t);
  round::def_surround<circle_t>(t);
  round::def_renormalize<point_pair_t>(t);
  round::def_renormalize<circle_t>(t);
  round::def_direction<point_pair_t>(t);
  round::def_direction<circle_t>(t);
  round::def_split<point_pair_t>(t);
  round::def_split<circle_t>(t);

  round::def_produce<vector_t>(t);
}

} // namespace cga

} // namespace pyversor
