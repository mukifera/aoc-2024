import sys
from collections import deque

numpad = {}
numpad['7'] = (0, 0)
numpad['8'] = (0, 1)
numpad['9'] = (0, 2)
numpad['4'] = (1, 0)
numpad['5'] = (1, 1)
numpad['6'] = (1, 2)
numpad['1'] = (2, 0)
numpad['2'] = (2, 1)
numpad['3'] = (2, 2)
numpad['0'] = (3, 1)
numpad['A'] = (3, 2)

dirpad = {}
dirpad['^'] = (0, 1)
dirpad['A'] = (0, 2)
dirpad['<'] = (1, 0)
dirpad['v'] = (1, 1)
dirpad['>'] = (1, 2)

delta = {}
delta['^'] = (-1, 0)
delta['<'] = (0, -1)
delta['v'] = (1, 0)
delta['>'] = (0, 1)

dir_buttons = [" ^A", "<v>"]
num_buttons = ["789", "456", "123", " 0A"]

def within_dirpad(x, y):
  return not(x==0 and y==0) and x >= 0 and x < 3 and y >= 0 and y < 2

def within_numpad(x, y):
  return not(x==0 and y==3) and x >= 0 and x < 3 and y >= 0 and y < 4

def get_next_positions(pos):
  ret = []
  (y, x) = dirpad[pos[-1]] 
  for move in ['^', '<', '>', 'v']:
    ny = y + delta[move][0] 
    nx = x + delta[move][1] 
    if not within_dirpad(nx, ny):
      continue
    npos = pos[:-1]
    npos += dir_buttons[ny][nx]
    ret.append(npos)

  i = len(pos) - 1
  while i > 0 and pos[i] == 'A':
    i -= 1
  if i == 0:
    return ret
  if i == 1:
    (y, x) = numpad[pos[i-1]]
  else:
    (y, x) = dirpad[pos[i-1]]
  ny = y + delta[pos[i]][0] 
  nx = x + delta[pos[i]][1] 
  if (i-1==0 and not within_numpad(nx, ny)) or (i-1 > 0 and not within_dirpad(nx, ny)):
    return ret
  npos = pos[:i-1]
  if i-1 == 0:
    npos += num_buttons[ny][nx]
  else:
    npos += dir_buttons[ny][nx]
  npos += pos[i:]
  ret.append(npos)
  return ret

def dfs(start, end):
  dist = {}
  dist[start] = 0
  q = deque()
  q.append(start)
  while len(q) != 0:
    pos = q.popleft()
    nxt = get_next_positions(pos)
    for npos in nxt:
      if npos not in dist:
        dist[npos] = 1e100
      if dist[npos] > dist[pos] + 1:
        dist[npos] = dist[pos] + 1
        q.append(npos) 

  return dist[end]
  

# def solve(code):
#   ans = int(code[:-1])

#   pos = (3, 2)
#   seq = ""
#   for ch in code:
#     next_pos = numpad[ch]
#     dr = next_pos[0] - pos[0]
#     dc = next_pos[1] - pos[1]
#     seq_1 = ""
#     seq_2 = ""
#     if dr > 0:
#       seq_2 += 'v' * dr
#     else:
#       seq_2 += '^' * -dr
#     if dc > 0:
#       seq_1 += '>' * dc
#     else:
#       seq_1 += '<' * -dc
#       seq_1, seq_2 = seq_2, seq_1

#     seq += seq_1 + seq_2 + 'A'
#     pos = next_pos
  
#   code = seq

#   pos = (0, 2)
#   for _ in range(2):
#     seq = ""
#     for ch in code:
#       next_pos = dirpad[ch]
#       dr = next_pos[0] - pos[0]
#       dc = next_pos[1] - pos[1]
#       seq_1 = ""
#       seq_2 = ""
#       if dr > 0:
#         seq_2 += 'v' * dr
#       else:
#         seq_2 += '^' * -dr
#       if dc > 0:
#         seq_1 += '>' * dc
#       else:
#         seq_1 += '<' * -dc
#         seq_1, seq_2 = seq_2, seq_1

#       seq += seq_1 + seq_2 + 'A'
#       pos = next_pos
    
#     code = seq

#   # print(len(code), ans)
#   print(code)
#   ans *= len(code)

#   return ans

def solve(code):
  pos = 'AAA'
  ans = len(code)
  for c in code:
    tar = c + 'AA'
    ans += dfs(pos, tar)
    pos = tar
  return ans * int(code[:-1])


ans = 0
for line in sys.stdin:
  line = line.strip('\n')
  ans += solve(line)
print(ans)
