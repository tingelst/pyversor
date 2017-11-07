from __pyversor__.cga.rounds import (carrier, center, curvature,
                                     direction, distance, location,
                                     normalize, null, produce, radius,
                                     renormalize, size, split,
                                     split_location, squared_distance,
                                     surround)


from ..import Vector as DualSphere
from ..import Bivector as PointPair
from ..import Trivector as Circle
from ..import Quadvector as Sphere


__round_types = [DualSphere, PointPair, Circle, Sphere]

PointPair.carrier = lambda self: carrier(self)
Circle.carrier = lambda self: carrier(self)
PointPair.direction = lambda self: direction(self)
Circle.direction = lambda self: direction(self)

DualSphere.distance = lambda self: distance(self)
DualSphere.null = lambda self: null(self)

for round_type in __round_types:
    round_type.center = lambda self: center(self)
    round_type.curvature = lambda self: curvature(self)
    round_type.location = lambda self: location(self)
    round_type.normalize = lambda self: normalize(self)
