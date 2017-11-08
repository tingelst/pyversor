from __pyversor__.cga import (
    Vector,
    Bivector,
    Trivector,
    Quadvector,
    Infinity,
    Origin,
    Pseudoscalar,
    Multivector
)

from . import generate
from . import operate
from . import construct
from . import flats
from . import rounds
from . import directions
from . import tangents
from . import versors


ni = Infinity(1.0)
no = Origin(1.0)

I = Pseudoscalar(1.0)
