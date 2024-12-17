#include <bits/stdc++.h>

using namespace std;

vector<string> grid;
vector<vector<bool>> f;
pair<int, int> ret;

int moves[4][2] = {{0,1}, {0,-1}, {1, 0}, {-1, 0}};

void solve(int i, int j) {
  ret.first++;
  for(int k=0; k<4; k++) {
    int ii = i+moves[k][0];
    int jj = j+moves[k][1];
    if(ii<0 || ii >= grid.size() || jj < 0 || jj >= grid[0].size()){
      ret.second++;
      continue;
    }
    if(grid[ii][jj] != grid[i][j]){
      ret.second++;
      continue;
    }
    if(f[ii][jj]) continue;
    f[ii][jj] = true;
    solve(ii, jj);
  }
}

int main() {

  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  f = vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size(), false));
  
  long long ans = 0;
  for(int i=0; i<grid.size(); i++) {
    for(int j=0; j<grid[0].size(); j++) {
      if(f[i][j]) continue;
      ret = {0, 0};
      f[i][j] = true;
      solve(i, j);
      ans += 1LL * ret.first * ret.second;
    }
  }

  cout << ans << "\n";

  return 0;
}