import sys

vec = []
for line in sys.stdin:
  vec = map(int, line.split(" "))

dp = {}

def rec(x, k):
  if (x,k) in dp:
    return dp[(x, k)]
  if k == 0:
    return 1
  if x == 0:
    dp[(x,k)] = rec(1, k-1)
  elif len(str(x))%2 == 0:
    d = len(str(x))
    a = int(str(x)[:d//2])
    b = int(str(x)[d//2:])

    dp[(x,k)] = rec(a, k-1) + rec(b, k-1)
  else:
    dp[(x,k)] = rec(x*2024, k-1)
  
  return dp[(x,k)]

ans = 0
for x in vec:
  ans += rec(x, 75)
print(ans)
