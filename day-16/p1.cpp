#include <bits/stdc++.h>

using namespace std;

int moves[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

bool in_bounds(int x, int y, const vector<string>& grid) {
  return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size();
}

int main() {

  string line;
  pair<int,int> start;
  pair<int,int> end;
  vector<string> grid;
  while (getline(cin, line)) {
    for(int i=0; i<line.size(); i++){
      if(line[i]=='S'){
        start.first = i;
        start.second = grid.size();
      } else if(line[i]=='E') {
        end.first = i;
        end.second = grid.size();
      }
    }
    grid.push_back(line);
  }
  
  vector<vector<vector<long long>>> dist(grid.size(), vector<vector<long long>>(grid[0].size(), vector<long long>(4, 1e18)));
  vector<vector<vector<bool>>> flag(grid.size(), vector<vector<bool>>(grid[0].size(), vector<bool>(4, false)));
  dist[start.second][start.first][0] = 0;
  queue<vector<int>> q;
  q.push({start.first, start.second, 0});
  flag[start.second][start.first][0] = true;
  while(!q.empty()){
    vector<int> vec = q.front();
    q.pop();
    int x = vec[0];
    int y = vec[1];
    int dir = vec[2];
    flag[y][x][dir] = false;
    vector<vector<int>> ops = {{x+moves[dir][1], y+moves[dir][0], dir, 1}, {x, y, (dir+1)%4, 1000}, {x, y, (dir+3)%4, 1000}};
    for(vector<int> op : ops){
      int xx = op[0];
      int yy = op[1];
      int dd = op[2];
      int cost = op[3];
      if(!in_bounds(xx, yy, grid) || grid[yy][xx] == '#' || dist[yy][xx][dd] <= dist[y][x][dir] + cost) continue;
      dist[yy][xx][dd] = dist[y][x][dir] + cost;
      if(!flag[yy][xx][dd]){
        q.push({xx, yy, dd});
        flag[yy][xx][dd] = true;
      }
    }
  }

  long long ans = 1e18;
  for(int i=0; i<4; i++){
    ans = min(ans, dist[end.second][end.first][i]);
  }

  cout << ans << "\n";

  return 0;
}