A = int(input()[12:])
B = int(input()[12:])
C = int(input()[12:])
input()
program = list(map(int,input()[9:].split(',')))

outs = []
ptr = 0

class Computer:

  def __init__(self, A, B, C):
    self.A = A
    self.B = B
    self.C = C

  def get_combo_operand(self):
    value = self.program[self.ptr+1]
    return [value, value, value, value, self.A, self.B, self.C, -1][value]

  def op_adv(self):
    operand = self.get_combo_operand()
    self.A = self.A // (2 ** operand)
    self.ptr += 2

  def op_bxl(self):
    operand = self.program[self.ptr+1]
    self.B = self.B ^ operand
    self.ptr += 2

  def op_bst(self):
    operand = self.get_combo_operand()
    self.B = operand % 8
    self.ptr += 2

  def op_jnz(self):
    if(self.A==0):
      self.ptr += 2
      return
    operand = self.program[self.ptr+1]
    self.ptr = operand

  def op_bxc(self):
    self.B = self.B ^ self.C
    self.ptr += 2

  def op_out(self):
    operand = self.get_combo_operand()
    self.outs.append(str(operand % 8))
    self.ptr += 2

  def op_bdv(self):
    operand = self.get_combo_operand()
    self.B = self.A // (2 ** operand)
    self.ptr += 2

  def op_cdv(self):
    operand = self.get_combo_operand()
    self.C = self.A // (2 ** operand)
    self.ptr += 2

  def run(self, program):
    self.ptr = 0
    self.outs = []
    self.program = program

    ops = [self.op_adv, self.op_bxl, self.op_bst, self.op_jnz, self.op_bxc, self.op_out, self.op_bdv, self.op_cdv]

    while self.ptr < len(self.program):
      opcode = self.program[self.ptr]
      ops[opcode]()

    return self.outs

computer = Computer(A, B, C)
outs = computer.run(program)
print(','.join(outs))