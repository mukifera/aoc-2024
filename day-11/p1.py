import sys

vec = []
for line in sys.stdin:
  vec = map(int, line.split(" "))

for _ in range(25):
  nv = []
  for x in vec:
    if x == 0:
      nv.append(1)
      continue
    if len(str(x))%2 == 0:
      d = len(str(x))
      a = int(str(x)[:d//2])
      b = int(str(x)[d//2:])
      nv.append(a)
      nv.append(b)
      continue
    nv.append(x*2024)
  vec = nv

print(len(vec))