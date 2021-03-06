# Copyright (c) 2015, Lars Tingelstad
# All rights reserved.
#
# All rights reserved.
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of pyversor nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""Operations on rounds in 3D conformal geometric algebra."""

from __pyversor__.c3d.tangents import (
    TangentVector, TangentBivector, TangentTrivector)


from __pyversor__.c3d.rounds import (carrier, center, curvature,
                                     direction, distance, location,
                                     normalize, null, produce, radius,
                                     renormalize, size, split,
                                     split_location, squared_distance,
                                     surround)


from .import Vector as DualSphere
from .import Bivector as PointPair
from .import Trivector as Circle
from .import Quadvector as Sphere


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
