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

comp_list = list(comps)

clique = []
ans = ""
def rec(i):
  global ans
  if i == len(comp_list):
    lst = ','.join(sorted(clique))
    if len(lst) > len(ans):
      ans = lst
    return
  rec(i+1)
  comp = comp_list[i]
  for c in clique:
    e = [c, comp]
    e.sort()
    if '-'.join(e) not in edges:
      return
  clique.append(comp)
  rec(i+1)
  clique.pop()

rec(0)

print(ans)

