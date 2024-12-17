#include <bits/stdc++.h>

using namespace std;

const int moves[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int main() {

  string line;
  vector<string> grid;
  vector<pair<int,int>> ends;
  while (getline(cin, line)) {
    for(int i=0; i<line.size(); i++){
      if(line[i] == '9') ends.push_back({grid.size(), i});
    }
    grid.push_back(line);
  }
  
  int ans = 0;

  for(int i=0; i<grid.size(); i++) {
    for(int j=0; j<grid[0].size(); j++) {
      if(grid[i][j] != '0') continue;
      vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), -1));
      dist[i][j] = 0;
      queue<pair<int,int>> q;
      q.push({i, j});
      while(!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        int y = p.first;
        int x = p.second;
        for(int k=0; k<4; k++) {
          int yy = y + moves[k][0];
          int xx = x + moves[k][1];
          if(xx<0 || xx >= grid[0].size() || yy<0 || yy >= grid.size() || grid[yy][xx] != grid[y][x] + 1) continue;
          if(dist[yy][xx] == -1) {
            dist[yy][xx] = dist[y][x] + 1;
            q.push({yy, xx});
          }
        }
      }

      for(pair<int,int> p : ends) {
        if(dist[p.first][p.second] == 9) ++ans;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}