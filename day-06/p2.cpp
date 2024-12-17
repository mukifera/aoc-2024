#include <bits/stdc++.h>

using namespace std;

vector<string> grid;
vector<vector<set<char>>> vis;

char rotate(char c) {
  switch(c) {
    case '<':
      return '^';
    case '>':
      return 'v';
    case '^':
      return '>';
    case 'v':
      return '<';
  }
  return '?';
}

pair<int,int> move(int x, int y, char dir) {
  switch(dir) {
    case '<':
      return {x - 1, y};
    case '>':
      return {x + 1, y};
    case '^':
      return {x, y - 1};
    case 'v':
      return {x, y + 1};
  }
  return {0, 0};
}

bool dfs(int x, int y, char dir) {
  int xx = x, yy = y;
  if(vis[y][x].count(dir) != 0) return true;
  pair<int,int> p = move(x, y, dir);
  xx = p.first, yy = p.second;
  if(xx<0 || xx >= grid[0].size() || yy < 0 || yy >= grid.size()) return false;
  while(grid[yy][xx] == '#'){
    dir = rotate(dir);
    p = move(x, y, dir);
    xx = p.first, yy = p.second;
  }
  vis[y][x].insert(dir);
  return dfs(xx, yy, dir);
}

int main() {

  string line;
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
  for(int i=0; i<grid.size(); i++) {
    for(int j=0; j<grid[0].size(); j++){
      if(i==pos.first && j==pos.second) continue;
      if(grid[i][j]=='#') continue;
      grid[i][j] = '#';
      vis.clear();
      vis = vector<vector<set<char>>>(grid.size(), vector<set<char>>(grid[0].size()));
      if(dfs(pos.second, pos.first, grid[pos.first][pos.second])){
        ++ans;
      }
      grid[i][j] = '.';
    }
  }
  cout << ans << "\n";

  return 0;
}