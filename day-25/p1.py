import sys

shape = []
locks = []
keys = []

def parse_shape(shape):
  heights = []
  for i in range(len(shape[0])):
    cnt = 0
    for j in range(len(shape)):
      if shape[j][i] == '#':
        cnt += 1
    heights.append(cnt) 

  if shape[0][0] == '#':
    locks.append((len(shape), heights))
  else:
    keys.append((len(shape), heights))

for line in sys.stdin:
  line = line.strip('\n')
  if line != "":
    shape.append(line)
    continue

  parse_shape(shape)
  shape = []

if len(shape) > 0:
  parse_shape(shape)
  
ans = 0
for key in keys:
  for lock in locks:
    good = True
    for i in range(len(key[1])):
      if key[1][i] + lock[1][i] > key[0]:
        good = False
        break
    if good:
      ans += 1
print(ans)