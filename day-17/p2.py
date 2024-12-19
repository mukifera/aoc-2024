
program = [2,4,1,1,7,5,1,5,4,0,5,5,0,3,3,0] 

def get_out(A):
  B = (A & 7) ^ 1
  return (B ^ (A >> B) ^ 5) & 7

def rec(A, n):
  if(n == 16):
    return A
  for i in range(8):
    nA = (A << 3) | i
    if(get_out(nA) != program[-n-1]):
      continue
    val = rec(nA, n+1)
    if(val != -1):
      return val
  return -1

print(rec(0, 0))
    