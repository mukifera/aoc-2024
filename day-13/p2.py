import sys

lines = [line for line in sys.stdin]
ans = 0
for i in range(0, len(lines), 3):
  a = list(map(int,lines[i].split(" ")))
  b = list(map(int,lines[i+1].split(" ")))
  t = list(map(int,lines[i+2].split(" ")))
  t[0] += 10000000000000
  t[1] += 10000000000000
  
  num = t[1]*b[0] - b[1]*t[0]
  deno = a[1]*b[0] - b[1]*a[0]
  if num % deno != 0:
    continue
  an = num // deno

  num = t[0] - an*a[0]
  deno = b[0]
  if num % deno != 0:
    continue
  bn = num // deno

  ans += 3*an + bn

print(ans)