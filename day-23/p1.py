import sys

fact = {}
def get_fact(x):
  if x < 2:
    return 1
  if x in fact:
    return fact[x]
  fact[x] = x * get_fact(x-1)
  return fact[x]

edges = set()
comps = set()
for line in sys.stdin:
  edge = line.strip('\n').split('-')
  edge.sort()
  edges.add('-'.join(edge))
  comps.add(edge[0])
  comps.add(edge[1])

ans = 0
for edge in edges:
  [a, b] = edge.split('-')
  for comp in comps:
    if comp == a or comp == b:
      continue
    if a[0] != 't' and b[0] != 't' and comp[0] != 't':
      continue
    e1 = [a, comp]
    e2 = [b, comp]
    e1.sort()
    e2.sort()
    if '-'.join(e1) in edges and '-'.join(e2) in edges:
      ans += 1

ans //= 3
print(ans)

