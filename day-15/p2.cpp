#include <bits/stdc++.h>

using namespace std;

int moves[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; 
pair<int,int> pos;
vector<string> grid;

enum direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

bool valid(int x, int y) {
  return x>=0 && x<grid[0].size() && y>=0 && y<grid.size();
}

bool blocked(int x, int y, direction dir) {
  if(grid[y][x]=='.') return false;
  if(grid[y][x]=='#') return true;
  if(grid[y][x]==']') --x;
  int dx = moves[dir][1];
  int dy = moves[dir][0];
  if(!valid(x+dx, y+dy)) return true;
  if(dir == UP || dir == DOWN) {
    return blocked(x, y+dy, dir) || blocked(x+1, y+dy, dir);
  }
  if(dir == RIGHT) dx++;
  return blocked(x+dx, y, dir);

}

void move_box(int x, int y, direction dir) {
  if(grid[y][x] == '.') return;
  if(grid[y][x] == ']') x--;
  int dx = moves[dir][1];
  int dy = moves[dir][0];
  if(dir == UP || dir == DOWN) {
    move_box(x, y+dy, dir);
    move_box(x+1, y+dy, dir);
    swap(grid[y][x], grid[y+dy][x]);
    swap(grid[y][x+1], grid[y+dy][x+1]);
    return;
  }
  if(dir == RIGHT){
    move_box(x+dx+1, y, dir);
    swap(grid[y][x+1], grid[y][x+1+dx]);
    swap(grid[y][x], grid[y][x+dx]);
  } else {
    move_box(x+dx, y, dir);
    swap(grid[y][x], grid[y][x+dx]);
    swap(grid[y][x+1], grid[y][x+1+dx]);
  }
}

void move_robot(direction dir) {
  int x = pos.first;
  int y = pos.second;
  int dx = moves[dir][1];
  int dy = moves[dir][0];
  int nx = x + dx;
  int ny = y + dy;
  if(!valid(nx, ny) || grid[ny][nx]=='#') return;
  if(grid[ny][nx] != '.'){
    if(blocked(nx, ny, dir)) return;
    move_box(nx, ny, dir);
  }
  swap(grid[y][x], grid[ny][nx]);
  pos.first += dx;
  pos.second += dy;
}

int main() {

  string line;
  while (getline(cin, line)) {
    if(line == "") break;
    string row = "";
    for(char c : line){
      if(c=='#') row += "##";
      else if(c=='@') row += "@.";
      else if(c=='.') row += "..";
      else row += "[]";
    } 
    for(int i=0; i<row.size(); i++){
      if(row[i]=='@'){
        pos.first = i;
        pos.second = grid.size();
      }
    }
    grid.push_back(row);
  }
  while (getline(cin, line)) {
    for(char c : line){
      for(int i=0; i<4; i++){
        if("^v<>"[i]==c) {
          move_robot((direction)i);
          break;
        }
      }
    }
  }
  
  long long ans = 0;
  for(int i=0; i<grid.size(); i++){
    for(int j=0; j<grid[0].size(); j++){
      if(grid[i][j]!='[') continue;
      ans += 100L*i+j;
    }
  }

  cout << ans << "\n";

  return 0;
}