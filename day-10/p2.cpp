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
  
  vector<vector<vector<long long>>> dp(grid.size(), vector<vector<long long>>(grid[0].size(), vector<long long>(10, 0)));
  for(int i=0; i<grid.size(); i++) {
    for(int j=0; j<grid[0].size(); j++) {
      if(grid[i][j] != '9') continue;
      dp[i][j][9] = 1;
    }
  }

  for(int k=8; k>=0; k--) {
    for(int i=0; i<grid.size(); i++) {
      for(int j=0; j<grid[0].size(); j++) {
        if(grid[i][j]-'0' != k) continue;
        for(int l=0; l<4; ++l) {
          int ii = i + moves[l][0];
          int jj = j + moves[l][1];
          if(ii < 0 || ii >= grid.size() || jj < 0 || jj >= grid[0].size() || grid[ii][jj] != grid[i][j] + 1) continue;
          dp[i][j][k] += dp[ii][jj][k+1];
        }
      }
    }
  }
  
  long long ans = 0;
  for(int i=0; i<grid.size(); i++) {
    for(int j=0; j<grid[0].size(); j++) {
      if(grid[i][j] != '0') continue;
      ans += dp[i][j][0];
    }
  }

  cout << ans << "\n";

  return 0;
}