#include <bits/stdc++.h>

using namespace std;

void dfs(int x, int y, vector<string>& grid) {
  int xx = x, yy = y;
  char nxt;
  char dir = grid[y][x];
  switch(dir) {
    case '<':
      xx = x - 1;
      nxt = '^';
      break;
    case '>':
      xx = x + 1;
      nxt = 'v';
      break;
    case '^':
      yy = y - 1;
      nxt = '>';
      break;
    case 'v':
      yy = y + 1;
      nxt = '<';
      break;
  }
  grid[y][x] = 'X';
  if(xx<0 || xx >= grid[0].size() || yy < 0 || yy >= grid.size()) return;
  if(grid[yy][xx] == '#'){
    grid[y][x] = nxt;
    dfs(x, y, grid);
    return;
  }
  grid[yy][xx] = dir;
  dfs(xx, yy, grid);
}

int main() {

  string line;
  vector<string> grid;
  pair<int,int> pos;
  while (getline(cin, line)) {
    for(int i=0; i<line.size(); i++) {
      char c = line[i];
      if(c=='^' || c=='<' || c=='>' || c=='v') {
        pos.first = grid.size();
        pos.second = i;
      }
    }
    grid.push_back(line);
  }
  
  int ans = 0;
  dfs(pos.second, pos.first, grid);

  for(string line : grid) {
    for(char c : line){
      if(c == 'X') ++ans;
    }
  }

  cout << ans << "\n";

  return 0;
}