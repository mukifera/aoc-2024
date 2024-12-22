import sys

mod = 16777216

ans = 0
for line in sys.stdin:
  num = int(line.strip('\n'))
  for i in range(2000):
    x = num * 64
    num ^= x
    num %= mod
    
    x = num // 32
    num ^= x
    num %= mod

    x = num * 2048
    num ^= x
    num %= mod

  ans += num

print(ans)