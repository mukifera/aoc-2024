import sys

ans = 0
for line in sys.stdin:
  line = line.strip('\n')
  [res, s_val] = line.split(':')
  nums = s_val.split(" ")[1:]
  res = int(res)
  for i in range(len(nums)):
    nums[i] = int(nums[i])

  def rec(i, tot):
    if(i == len(nums)):
      return tot == res
    if(i == 0):
      return rec(i+1, nums[0])
    if(rec(i+1, tot + nums[i])):
      return True
    return rec(i+1, tot * nums[i])

  if(rec(0, 0)):
    ans += res

print(ans)