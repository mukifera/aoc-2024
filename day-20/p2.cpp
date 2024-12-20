#include <bits/stdc++.h>

using namespace std;

const int moves[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

vector<string> grid;

vector<vector<int>> get_dist(pair<int,int> start, pair<int,int> end) {
  vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), 1e9));
  dist[start.second][start.first] = 0;
  queue<pair<int,int>> q;
  q.push(start);
  while(!q.empty()){
    pair<int,int> p = q.front();
    q.pop();
    for(int i=0; i<4; i++){
      int x = p.first + moves[i][0];
      int y = p.second + moves[i][1];
      if(x<0 || x>=grid[0].size() || y<0 || y >= grid.size() || grid[y][x]=='#') continue;
      if(dist[y][x] <= dist[p.second][p.first] + 1) continue;
      dist[y][x] = dist[p.second][p.first] + 1;
      q.push({x, y});
    }
  }
  return dist;
}

int main() {

  string line;
  pair<int,int> start, end;
  while (getline(cin, line)) {
    for(int i=0; i<line.size(); i++){
      if(line[i] == 'S'){
        start.first = i;
        start.second = grid.size();
      } else if (line[i] == 'E'){
        end.first = i;
        end.second = grid.size();
      }
    }
    grid.push_back(line);
  }
  
  vector<vector<int>> s2e = get_dist(start, end);
  vector<vector<int>> e2s = get_dist(end, start);

  int ans = 0;
  int best = s2e[end.second][end.first];
  for(int i=0; i<grid.size(); i++){
    for(int j=0; j<grid[0].size(); j++){
      if(grid[i][j]=='#') continue;
      for(int ii=i-20; ii<=i+20; ii++){
        if(ii<0 || ii>=grid.size()) continue;
        int left = 20 - abs(i-ii);
        for(int jj=j-left; jj<=j+left; jj++){
          if(jj<0 || jj>=grid[0].size()) continue;
          if(grid[ii][jj]=='#') continue;
          int cost = abs(i-ii) + abs(j-jj);
          cost += s2e[i][j];
          cost += e2s[ii][jj];
          if(best-cost >= 100){
            ++ans;
          }
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}