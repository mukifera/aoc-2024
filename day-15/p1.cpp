#include <bits/stdc++.h>

using namespace std;

int moves[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; 
pair<int,int> pos;
vector<string> grid;

bool valid(int x, int y) {
  return x>=0 && x<grid[0].size() && y>=0 && y<grid.size();
}

void move(int dir) {
  int x = pos.first;
  int y = pos.second;
  int dx = moves[dir][1];
  int dy = moves[dir][0];
  int nx = x, ny = y;
  while(true){
    if(!valid(nx+dx, ny+dy)) break;
    nx += dx;
    ny += dy;
    if(grid[ny][nx]!='O') break;
  }
  if(!valid(nx, ny) || grid[ny][nx]=='#') return;
  swap(grid[y+dy][x+dx], grid[ny][nx]);
  swap(grid[y][x], grid[y+dy][x+dx]);
  pos.first += dx;
  pos.second += dy;
}

int main() {

  string line;
  while (getline(cin, line)) {
    if(line == "") break;
    for(int i=0; i<line.size(); i++){
      if(line[i]=='@'){
        pos.first = i;
        pos.second = grid.size();
      }
    }
    grid.push_back(line);
  }
  while (getline(cin, line)) {
    for(char c : line){
      for(int i=0; i<4; i++){
        if("^v<>"[i]==c) {
          move(i);
          break;
        }
      }
    }
  }
  
  long long ans = 0;
  for(int i=0; i<grid.size(); i++){
    for(int j=0; j<grid[0].size(); j++){
      if(grid[i][j]!='O') continue;
      ans += 100L*i+j;
    }
  }

  cout << ans << "\n";

  return 0;
}