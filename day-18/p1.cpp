#include <bits/stdc++.h>

using namespace std;

const int LEN = 71;
const int NBYTES = 1024;
const int moves[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int main() {

  string line;
  vector<pair<int,int>> arr;
  vector<vector<bool>> safe(LEN, vector<bool>(LEN, true));
  while (getline(cin, line)) {
    stringstream ss(line);
    int x, y;
    char c;
    ss >> x >> c >> y;
    arr.push_back({x, y});
  }

  for(int i=0; i<NBYTES; i++){
    safe[arr[i].second][arr[i].first] = false;
  }

  vector<vector<int>> dist(LEN, vector<int>(LEN, 1e9));
  dist[0][0] = 0;
  queue<pair<int,int>> q;
  q.push({0, 0});
  while(!q.empty()){
    pair<int,int> p = q.front();
    q.pop();
    for(int i=0; i<4; i++){
      int xx = p.first + moves[i][0];
      int yy = p.second + moves[i][1];
      if(xx<0 || xx>=LEN || yy<0 || yy>=LEN || !safe[yy][xx]) continue;
      if(dist[yy][xx] <= dist[p.second][p.first] + 1) continue;
      dist[yy][xx] = dist[p.second][p.first] + 1;
      q.push({xx, yy});
    }
  }

  cout << dist[LEN-1][LEN-1] << "\n";

  return 0;
}