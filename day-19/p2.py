import sys

towels = input().split(", ")
input()

ans = 0
for line in sys.stdin:
  line = line[:-1]

  dp = {}
  def rec(i):
    if(i==len(line)):
      return 1
    if(i in dp):
      return dp[i]
    ret = 0
    for towel in towels:
      if(i+len(towel) > len(line)):
        continue
      if(towel != line[i:i+len(towel)]):
        continue
      ret += rec(i+len(towel))
    dp[i] = ret
    return ret

  ans += rec(0)

print(ans)