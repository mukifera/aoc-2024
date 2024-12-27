import sys
from PIL import Image, ImageColor

W = 101
H = 103

bots = []
for line in sys.stdin:
  [px, py, vx, vy] = list(map(int, line.split(" ")))
  vx = (vx+W)%W
  vy = (vy+H)%H
  bots.append([px, py, vx, vy])
  i = 0
  bot_id = len(bots)-1
  while True:
    i += 1
    px = (px+vx+W)%W
    py = (py+vy+H)%H
    if(px == bots[bot_id][0] and py == bots[bot_id][1]):
      break
  assert(i == W*H)



def draw_grid_at_time(t, img, offset_x, offset_y):
  for bot in bots:
    [px, py, vx, vy] = bot
    px = (px + t * vx) % W
    py = (py + t * vy) % H
    img.putpixel((px+offset_x, py+offset_y), ImageColor.getcolor('white', '1'))


def draw_grids(from_time, to_time):
  frame_count = to_time - from_time + 1
  max_per_row = 19
  per_row = min(max_per_row, frame_count)
  image_width = per_row * W
  image_height = H * ((frame_count + per_row - 1) // per_row)
  img = Image.new('1', (image_width, image_height))

  row = 0
  col = 0
  for i in range(from_time, to_time+1):
    if col == per_row:
      col = 0
      row += 1
    offset_x = col * W
    offset_y = row * H
    draw_grid_at_time(i, img, offset_x, offset_y)
    col += 1

  img.putpixel((1000, 500), ImageColor.getcolor('white', '1'))
  img.save('grids.png')


draw_grids(0, W * H)
