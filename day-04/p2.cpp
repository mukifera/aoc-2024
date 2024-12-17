#include <bits/stdc++.h>

using namespace std;


int main() {

  string line;
  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  
  int moves[4][2] = {{0,0}, {2,0}, {2,2}, {0,2}};
  
  int n = grid.size();
  int m = grid[0].size();

  int ans = 0;
  string per = "MMSS";
  for(int i=0; i+2<n; i++) {
    for(int j=0; j+2<m; j++) {
      if(grid[i+1][j+1] != 'A') continue;
      bool good = true;
      for(int k=0; k<4; k++) {
        good = true;
        for(int l=0; l<4; l++) {
          int ii = moves[(l+k)%4][0] + i;
          int jj = moves[(l+k)%4][1] + j;
          if(grid[ii][jj] != per[l]){
            good = false;
            break;
          }
        }
        if(good) break;
      }
      if(good) ans++;
    }
  }

  cout << ans << "\n";

  return 0;
}