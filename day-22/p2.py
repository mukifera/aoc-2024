import sys

mod = 16777216

mp = {}
for line in sys.stdin:
  num = int(line.strip('\n'))
  changes = []
  st = set()
  for i in range(2000):
    prv = num
    x = num << 6
    num ^= x
    num &= (1<<24)-1
    
    x = num >> 5
    num ^= x
    num &= (1<<24)-1

    x = num << 11
    num ^= x
    num &= (1<<24)-1

    changes.append((num%10) - (prv%10))
    if len(changes) < 4:
      continue
    lst = str(changes[-4:])
    if lst in st:
      continue
    st.add(lst)
    if lst not in mp:
      mp[lst] = 0
    mp[lst] += num%10

ans = 0
for v in mp.values():
  ans = max(ans, v)


print(ans)