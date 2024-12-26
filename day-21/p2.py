import sys
from collections import deque

PAD_COUNT = 26

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

dir2id = {}
dir2id['^'] = 0
dir2id['A'] = 1
dir2id['<'] = 2
dir2id['v'] = 3
dir2id['>'] = 4

num2id = {}
num2id['7'] = 0
num2id['8'] = 1
num2id['9'] = 2
num2id['4'] = 3
num2id['5'] = 4
num2id['6'] = 5
num2id['1'] = 6
num2id['2'] = 7
num2id['3'] = 8
num2id['0'] = 9
num2id['A'] = 10

id2num = "7894561230A"
id2dir = "^A<v>"

memo = [[[-1 for _ in range(PAD_COUNT)] for _ in range(11)] for _ in range(11)]

def within_dirpad(x, y):
  return not(x==0 and y==0) and x >= 0 and x < 3 and y >= 0 and y < 2

def within_numpad(x, y):
  return not(x==0 and y==3) and x >= 0 and x < 3 and y >= 0 and y < 4

def get_key_id(code, pad_index):
  if pad_index == 0:
    return num2id[code]
  else:
    return dir2id[code]

def get_cost(start, end, pad_index):
  if pad_index == PAD_COUNT:
    return 0
  if memo[start][end][pad_index] != -1:
    return memo[start][end][pad_index]
  state = (start, get_key_id('A', pad_index + 1))
  dist = [[-1 for _ in range(11)] for _ in range(11)]
  flag = [[False for _ in range(11)] for _ in range(11)]
  dist[state[0]][state[1]] = 0
  q = deque()
  q.append(state)
  flag[state[0]][state[1]] = True
  while len(q) != 0:
    cur = q.popleft()
    flag[cur[0]][cur[1]] = False
    y, x = 0, 0
    if pad_index == 0:
      (y, x) = numpad[id2num[cur[0]]]
    else:
      (y, x) = dirpad[id2dir[cur[0]]]
    for move in ['^', '<', '>', 'v']:
      ny = y + delta[move][0] 
      nx = x + delta[move][1] 
      if (pad_index == 0 and not within_numpad(nx, ny)) or (pad_index > 0 and not within_dirpad(nx, ny)):
        continue
      move_id = get_key_id(move, pad_index + 1)
      cost = get_cost(cur[1], move_id, pad_index + 1) + 1
      nxt = None
      if pad_index == 0:
        nxt = (get_key_id(num_buttons[ny][nx], pad_index), move_id)
      else:
        nxt = (get_key_id(dir_buttons[ny][nx], pad_index), move_id)
      if (dist[nxt[0]][nxt[1]] == -1) or (dist[nxt[0]][nxt[1]] > dist[cur[0]][cur[1]] + cost):
        dist[nxt[0]][nxt[1]] = dist[cur[0]][cur[1]] + cost
        if not flag[nxt[0]][nxt[1]]:
          flag[nxt[0]][nxt[1]] = True
          q.append(nxt)
  to = 0
  if pad_index == 0:
    to = len(num2id)
  else:
    to = len(dir2id)

  for i in range(to):
    memo[start][i][pad_index] = 1e100
  for i in range(to):
    for j in range(5):
      if dist[i][j] == -1:
        continue
      memo[start][i][pad_index] = min(memo[start][i][pad_index], dist[i][j] + get_cost(j, get_key_id('A', pad_index + 1), pad_index + 1))

  return memo[start][end][pad_index]

def solve(code):
  ans = len(code)
  cur = 'A'
  for nxt in code:
    ans += get_cost(num2id[cur], num2id[nxt], 0)
    cur = nxt
  return ans * int(code[:-1])

ans = 0
for line in sys.stdin:
  line = line.strip('\n')
  ans += solve(line)
print(ans)