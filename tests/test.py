import sys
sys.path.append('build')
import numpy.random as rnd

import pyversor
print(dir(pyversor))

a = pyversor.cga.round.null(pyversor.ega.Vector(1,2,3))
print(a)

from pyversor import ega, cga
# from pyversor.cga.round import null

a = ega.Vector(1,2,3)
print(a)

B = a.undual()
print(B)

R = 1 + B
print(R)

print(R.grade(2))

a = ega.Bivector(1,2,3)
R = 1.0 + a

print(R)

s = R.grade(0)
B = R.grade(2)

print(s)
print(B)

print(R.grade(3))

print("Conformal")
a = cga.Vector(*rnd.randn(5))
print(a)

ap = a.spin(R)
print(a)

a = ega.Multivector(*rnd.randn(8))

b = ega.Multivector(a)
print(a)
print(b)

print("Projected")
print(ega.Rotator(b))


print(cga.round.null(ega.Vector(1,2,3)))

a = cga.Vector(*rnd.randn(5))
print(a)
print(cga.round.radius(a))
print(cga.round.radius(a.undual()))

print(cga.round.null(a))
print(cga.round.radius(cga.round.null(a)))