import pyversor as vsr

a = vsr.Biv(1,2,3)
R = 1.0 + a

print(R)

s = R.grade(0)
B = R.grade(2)

print(s)
print(B)
print(R.grade(1))