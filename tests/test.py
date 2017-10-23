import sys
sys.path.append('build')
import numpy.random as rnd
from pyversor import ega, cga

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

a = cga.Multivector()
print(a)

