from . import ega
from . import cga
from . import visuals

_types = [cga.Vector, cga.Bivector, cga.Trivector, cga.Quadvector]
for t in _types:
    t.__repr__ = lambda self: self.toarray().__repr__()
    t.__str__ = lambda self: self.toarray().__str__()
