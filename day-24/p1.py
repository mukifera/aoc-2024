import sys

vals = {}
for line in sys.stdin:
  line = line.strip('\n')
  if line == "":
    break
  [a, b] = line.split(": ")
  vals[a] = int(b)

eqs = []
for line in sys.stdin:
  line = line.strip('\n')
  ops = line.split(" ")
  a = ops[0]
  b = ops[2]
  c = ops[4]
  eqs.append(ops)

f = [False for _ in range(len(eqs))]
cnt = 0
while cnt < len(eqs):
  for i in range(len(eqs)):
    if f[i]:
      continue
    ops = eqs[i]
    a = ops[0]
    b = ops[2]
    c = ops[4]
    op = ops[1]
    if a not in vals or b not in vals:
      continue
    v = 0
    if op == "AND":
      v = vals[a] & vals[b]
    elif op == "OR":
      v = vals[a] | vals[b]
    else:
      v = vals[a] ^ vals[b]
    vals[c] = v
    f[i] = True
    cnt += 1

ans = 0
for k in vals:
  if k[0] != 'z':
    continue
  if vals[k] == 0:
    continue
  ans = ans | (1 << (int(k[1:])))

print(ans)