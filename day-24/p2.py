import sys
from collections import deque

for line in sys.stdin:
  line = line.strip('\n')
  if line == "":
    break

rev = {}
graph = {}
for line in sys.stdin:
  line = line.strip('\n')
  ops = line.split(" ")
  a = ops[0]
  b = ops[2]
  c = ops[4]
  if a > b:
    a, b = b, a
  op = ops[1]
  rev[c] = [a, op, b]
  if a not in graph:
    graph[a] = []
  if b not in graph:
    graph[b] = []
  graph[a].append(c)
  graph[b].append(c)

def get_deps(out):
  expected = set()
  to = int(out[1:])
  for i in range(to+1):
    expected.add("x" + str(i).zfill(2))
    expected.add("y" + str(i).zfill(2))

  def rec(var):
    st = set()
    if var not in rev:
      st.add(var)
    else:
      op = rev[var]
      a = rec(op[0])
      b = rec(op[2])
      st = a.union(b)
    
    if len(st.difference(expected)):
      print(var)
    return st

  st = rec(out)
  if len(st) != len(expected):
    print(expected.difference(st))

def get_dependants(in_var):
  expected = set()
  from_i = int(in_var[1:])
  for i in range(from_i, 46):
    expected.add("z" + str(i).zfill(2))

  def rec(var):
    st = set()
    if var not in graph:
      st.add(var)
    else:
      for v in graph[var]:
        st.update(rec(v))
    return st

  st = rec(in_var)
  if len(st) != len(expected):
    print(expected.difference(st))


def get_def(out):

  def rec(var):
    if var not in rev:
      return ("", var)
    ops = rev[var]
    left = rec(ops[0])
    right = rec(ops[2])
    if len(left[1]) == len(right[1]):
      if left[0] > right[0]:
        left, right = right, left
    elif len(left[1]) > len(right[1]):
      left, right = right, left
    return (ops[1], f'({left[1]} {ops[1]} {right[1]})')
  
  return rec(out)[1]


for i in range(46):
  s = 'z' + str(i).zfill(2)
  eq = get_def(s)
  print(s, "=", eq)
  for j in range(i):
    ss = str(j).zfill(2)
    op = f'x{ss} AND y{ss}'
    if op not in eq:
      break