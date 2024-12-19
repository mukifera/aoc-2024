import sys

towels = input().split(", ")
input()

ans = 0
for line in sys.stdin:
  line = line[:-1]

  vis = set()
  def rec(i):
    if(i==len(line)):
      return True
    if(i in vis):
      return False
    for towel in towels:
      if(i+len(towel) > len(line)):
        continue
      if(towel != line[i:i+len(towel)]):
        continue
      if(rec(i+len(towel))):
        return True
    vis.add(i)
    return False

  if(rec(0)):
    ans += 1

print(ans)