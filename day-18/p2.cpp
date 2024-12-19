#include <bits/stdc++.h>

using namespace std;

const int LEN = 71;
const int moves[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
vector<pair<int,int>> arr;

bool reachable(int to_byte){
  vector<vector<bool>> safe(LEN, vector<bool>(LEN, true));
  for(int i=0; i<=to_byte; i++){
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
  return dist[LEN-1][LEN-1] != 1e9;
}

int main() {

  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    int x, y;
    char c;
    ss >> x >> c >> y;
    arr.push_back({x, y});
  }

  int lo = 0;
  int hi = arr.size();
  int mid;
  while(lo+1<hi){
    mid = (lo+hi)/2;
    if(reachable(mid)) lo = mid;
    else hi = mid;
  }

  cout << arr[hi].first << "," << arr[hi].second << "\n";

  return 0;
}