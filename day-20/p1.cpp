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
  
  int ans = 0;
  vector<vector<int>> s2e = get_dist(start, end);
  vector<vector<int>> e2s = get_dist(end, start);

  int best = s2e[end.second][end.first];
  for(int i=0; i<grid.size(); i++){
    for(int j=0; j<grid[0].size(); j++){
      if(grid[i][j]!='#') continue;
      vector<pair<int,int>> empties;
      for(int k=0; k<4; k++){
        int ii = i+moves[k][1];
        int jj = j+moves[k][0];
        if(ii<0 || ii>=grid.size() || jj<0 || jj>=grid[0].size() || grid[ii][jj]=='#') continue;
        empties.push_back({jj, ii}) ;
      }
      bool good = false;
      for(int ki=0; ki<empties.size(); ki++){
        for(int kj=0; kj<empties.size(); kj++){
          if(ki==kj) continue;
          int cost = 2;
          cost += s2e[empties[ki].second][empties[ki].first];
          cost += e2s[empties[kj].second][empties[kj].first];
          if(best-cost >= 100){
            good = true;
            break;
          }
        }
        if(good) break;
      }
      if(good) ++ans;
    }
  }

  cout << ans << "\n";

  return 0;
}